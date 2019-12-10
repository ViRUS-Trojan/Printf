/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:04:43 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/10 16:30:01 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void        handle_escape(t_vfpf *p)
{
    int pf;

    pf = p->flags;
    if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
        pad_width(p, 1);
        buff(p, "%", 1);
    if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
        pad_width(p, 1);
}

void        handle_n(t_vfpf *p)
{
    if (p->flags & T_FLAG)
		*va_arg(p->args, ptrdiff_t *) = (ptrdiff_t)p->len;
    else if (p->flags & Z_FLAG)
		*va_arg(p->args, ssize_t *) = (ssize_t)p->len;
    else if (p->flags & J_FLAG)
		*va_arg(p->args, intmax_t *) = (intmax_t)p->len;
    else if (p->flags & LL_FLAG)
        *va_arg(p->args, long long int *) = (long long int)p->len;
    else if (p->flags & L_FLAG)
        *va_arg(p->args & long int *) = (long int)p->len;
    else if (p->flags & H_FLAG)
        *va_arg(p->args & short int *) = (short int)p->len;
    else if (p->flags & HH_FLAG)
        *va_arg(p->args & signed char *) = (signed char)p->len;
    else
        *va_arg(p->args, int *) = (int)p->len;
}