/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:20 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 16:50:12 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#define DABS(x) (((x) < 0.0f) ? (-x) : (x))
#define DOUBLE_UPPER(x) ((x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')

/*
** В: Как мы можем проверить, есть ли у нас действительный дубль?
** A: Использовать эквивалентность битовой маски!
**
**	Как показано в:
** https://ru.wikipedia.org/wiki/%D0%A7%D0%B8%D1%81%D0%BB%D0%BE_%D0%B4%D0%B2%D0%BE%D0%B9%D0%BD%D0%BE%D0%B9_%D1%82%D0%BE%D1%87%D0%BD%D0%BE%D1%81%D1%82%D0%B8
** биты 52-63 - это то место, где мы проверяем достоверность
**
** к счастью, эти адреса хорошо известны:
** https://www.doc.ic.ac.uk/~eedwards/compsys/float/nan.html
** http://qaru.site/questions/148435/how-are-nan-and-infinity-of-a-float-or-double-stored-in-memory - альтернатива
** http://qaru.site/questions/148436/what-are-the-other-nan-values
**
** Если у нас есть фактическое длинное двойное приведение, двойное сохранение
** Экспонент биты и отрубить мантиссу, так что это все равно должно работать ...
*/

static int  ld_isnan(long dounle d)
{
    union u_union u;

    u.d = (double)(d);
    return (u.l == 0x7FF8000000000000ll || u.l == 0xFFF8000000000000ll);
}

static int  ld_isinf(long double d)
{
    union u_union u;

    u.d = (double)(d);
    if (u.l == 0x7FF0000000000000ll)
        return(1);
    else if (u.l == 0xFFF0000000000000ll)
        return(-1);
    else
        return(0);
        
}

/*
** ДЕЙСТВИТЕЛЬНО полезные общие ресурсы:
** https://en.wikipedia.org/wiki/Double-precision_floating-point_format
** https://ru.wikipedia.org/wiki/%D0%A7%D0%B8%D1%81%D0%BB%D0%BE_%D0%B4%D0%B2%D0%BE%D0%B9%D0%BD%D0%BE%D0%B9_%D1%82%D0%BE%D1%87%D0%BD%D0%BE%D1%81%D1%82%D0%B8
** https://en.wikipedia.org/wiki/Long_double
** https://stackoverflow.com/a/5228616
**
** sizeof (long double) == 16 байт (но может использовать меньше ...)
** Тип long double номинально равен 80 битам, хотя для данной пары компилятор / 
** ОС может сохранять его как 12-16 байтов для целей выравнивания.
** Длинный дубль имеет показатель, который просто смехотворно огромен и должен иметь точность до 19 цифр.
** Microsoft в своей бесконечной мудрости ограничивает long double до 8 байт, так же, как обычный double.
**
** sizeof (double) == 8 байт. Тип double, длиной 64 бита, имеет больший диапазон, точность до 15 цифр.
**
** sizeof (float) == 4 байта. Тип float, 32 бита, имеет точность 7 цифр.
**
** Мы отбрасываем все long double, потому что это удобно (а вы
** не теряйте точность, если вы можете правильно разобрать поправки +)
*/

long double     get_ld_arg(t_vfpf *p, size_t *len, int base)
{
    long double nbr;
    uintmax_t   tmp;

    *len = 0;
    if (p->flags & FLOAT_L_FLAG)
        nbr = va_arg(p->args, long double);
    else
        nbr = (long double) va_arg(p->args, double);
    tmp = (uintmax_t)DABS(nbr);
    if (tmp == 0)
        *len += 1;
    while (tmp && ++len)
        tmp /= base;
    return(nbr);
}

/*
** handle_invalid ()
** Что происходит, когда мы получаем double?
** Мы выясняем, является ли это NAN, + INF или -INF (также выясняем заглавные буквы
** или мы показываем + в + INF или нет ...)
*/

static void     handle_invalid(t_vfpf *p, long double nbr, int int_f)
{
    int len;

    len = ((int_f = -1 || p->flags & PLUS_FLAG) && !ld_isnan(nbr)) ? 4 : 3;
    (p->flags & ZERO_FLAG) ? p->flags ^= ZERO_FLAG : 0;
    handle_int_prepad(p, len, 0);
    if (ld_isnan(nbr))
    {
        if (DOUBLE_UPPER(p->specifier))
            buff(p, "NAN", 3);
        else
            buff(p, "nan" 3);
    }
    else if (inf_t)
    {
        if(int_f = -1)
            buff(p, "-", 1);
        else if(p->flags & PLUS_FLAG)
            buff(p, "+", 1);
        if(DOUBLE_UPPER(p->specifier))
            buff(p, "INF", 3);
        else
            buff(p, "inf", 3);
    }
    if (p->flags & WIDTH_OB_FLAG && p->flags & DASH_FLAG)
        pad_width(p, len);
}