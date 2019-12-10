/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:30:30 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/11 01:30:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <wchar.h>

/*
** Рабочая версия
*/

void    handle_wchar(t_vfpf *p)
{
    int     pf;
    wint_t  wc;

    pf = p->flags;
    wc = (wchar_t)va_arg(p->args, wint_t);
    if (pf & WIDTH_OB_FLAG && ! (pf & DASH_FLAG)
        pad_width(p, 1);
    pf_putwchar(p, wc);
    if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
        pad_width(p, 1);
}

/*
** Умышленно покалеченная версия!
**
**
** void handle_wchar (t_vfpf * p)
** {
** INT пф;
** wint_t туалет;
**
** pf = p-> flags;
** wc = (char) va_arg (p-> args, wint_t);
** if (pf & WIDTH_OB_FLAG &&! (pf & DASH_FLAG))
** pad_width (p, 1);
** бафф (p, & wc, 1);
** if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
** pad_width (p, 1);
**}
* /

/ *
** handle_char ()
** Наш общий обработчик символов, если мы имеем дело с широкими символами (юникод), то
** отправьте его обработчику wchar, в противном случае напишите:
** 1) левый отступ (если применимо)
** 2) Наш персонаж
** 3) правый отступ (если применимо)
*/

void    handle_char(t_vfpf *p)
{
    int     pf;
    char    c;

    pf = p->flags;
    if (pf & L_FLAG || p->specifier == 'C')
        handle_wchar(p);
    else
    {
        c = (char)va_arg(p->args, int);
        if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
            pad_width(p, 1);
        buff(p, &c, 1);
        if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
            pad_width(p, 1);
    }
}

/*
** calc_precision ()
** Поскольку символы utf-8 могут иметь ширину более 1 символа, у нас могут быть ситуации
** где указанная точность имеет больше символов, чем число печатаемых
** UTF-9 символов.
**
** Пример: ft_printf ("|% 15.4S |", L "我 是 一只 猫。");
** Указана точность 4, но utf char '我' 'имеет ширину 3' char '
** и символ '是' не может быть напечатан, если осталось только 1 символ 'точности'.
**
** Поэтому используйте рекурсивный вызов для пересчета нашей точности, чтобы
** точность будет обрезана до того, сколько может быть UTF символов
** успешно отображается.
**
** 1) Если широкий конец в конце или мы исчерпали нашу точность,
** вернуть наш new_prec (ision)
** 2) В противном случае, если текущий широкий строковый символ равен 1 байту, вычтите 1 из
** желаемая точность и добавьте единицу к нашему new_prec (ision).
** 3) В противном случае, если текущий широкий строковый символ имеет длину 2 байта, и мы имеем в
** как минимум еще 2 значения в нашей желаемой точности, затем вычтите 2 из нашего
** желаемой точности и добавьте 2 к нашему new_prec (ision).
** 4) Еще несколько шагов ...
** 5) Процесс заканчивается, когда у нас либо широкий символ больше 0x10FFFF
** или когда нам больше не хватает желаемой точности для удержания другого
** широкий символ
*/

size_t      calc_precision(wchar_t *str, int precision, size_t new_prec)
{
    if (*str == '\0' || precision == 0)
        return (new_prec);
    else if (*str <= 0x007F)
		return (calc_precision(str + 1, precision - 1, new_prec + 1));
	else if (*str <= 0x07FF && precision >= 2)
		return (calc_precision(str + 1, precision - 2, new_prec + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (calc_precision(str + 1, precision - 3, new_prec + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (calc_precision(str + 1, precision - 4, new_prec + 4));
	else
		return (new_prec);
}