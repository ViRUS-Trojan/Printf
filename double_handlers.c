/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:20 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/18 12:22:00 by vdelsie          ###   ########.fr       */
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

/*
** handle_double ()
**
** Имя функции ложь! (Тот тоже !!!)
**
** Основная стратегия состоит в том, чтобы понять, что мы можем отделить любое плавающее
** указывают на часть int и часть дроби. (например: 125,25 -> 125 и 25)
** мы можем легко получить доступ к части int с помощью актерского состава.
**
** ================================================ ===========================
**
** СУПЕР ВАЖНОЕ ПРИМЕЧАНИЕ: у этого метода есть серьезный недостаток, который он не может решить
** с даже полными представлениями типа «float», «double» и «long double».
**
** Это можно проверить, сравнив следующее с системой printf:
** #include <float.h>
** ft_printf («тестирование |% f | \ n», FLT_MAX);
** ft_printf («тестирование |% f | \ n», DBL_MAX);
** ft_printf («тестирование |% Lf | \ n», LDBL_MAX);
** FLT_MAX, например: 340282346638528859811704183484516925440
**
** Борьба с настоящими «float», «double» и «long double» была бы огромной задачей
** См .: https://stackoverflow.com/questions/1218149/
**
** ================================================ ===========================
**
** 1) Пока мы получаем приведение va_arg как long double, также посчитаем
** компонент нашего длинного двойника (то есть часть перед десятичной дробью '.')
** 2) Проверьте, является ли наш nbr недопустимым типом (INF, NAN, -INF) и обработайте его ...
** 3) «aAfFeEgG» по умолчанию с точностью до 6 (если точность не указана
** или если точность является бессмысленным числом)
** 4) Если у нас есть точность, которая не равна 0, или у нас есть флаг '#', мы
** установите для нашего общего значения nbr_len значение 1 (для учета символа '.'), в противном случае - 0.
** 5) Нам нужно учитывать ',' если у нас включен режим апострофа
** 6) Наша общая двойная длина такова: «целочисленная часть +». + точность "
** 7) Сделайте предварительную добавку (как обычно), тогда ВРЕМЯ ПРЕОБРАЗОВАТЬ!
*/

void    handle_double(t_vfpf *p)
{
    long double nbr;
    size_t      int_len;
    size_t      tot_len;

    p->base = 10;
    nbr = get_ld_arg(p, &int_len, p->base);
    if (ld_isinf(nbr) || ls_isnan(nbr))
        handle_invalid(p, nbr, ld_isinf(nbr));
    else
    {
        if (!(p->flags & PRECI_OB_FLAG) || p->precision < 0)
            p->precision = 6;
        tot_len = (p->precision != 0 || p->flags & HASH_FLAG) ? 1 : 0;
        p->neg = (nbr < 0.0) ? 1 : 0;
        int_len += (p->flags & APOST_FLAG) ? ((int_len - 1) / 3) : 0;
        tot_len += int_len + p->precision;
        if (nbr < 0.0 || p->flags & PLUS_FLAG || p->flags & SPACE_FLAG)
            p->width--;
        handle_double_prepad(p, tot_len);
        pf_lditoa_base(p, nbr, int_len, tot_len);
        if (p->flags & WIDTH_OB_FLAG && p->flags & DASH_FLAG)
            pad_width(p, tot_len);
    }
}