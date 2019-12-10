/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:30:30 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/10 16:59:24 by vdelsie          ###   ########.fr       */
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