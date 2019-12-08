/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:16:26 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/08 18:58:12 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#define UPPER(x) ((x)=='X'||(x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')
#define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p'||(x)=='a'||(x)=='A')

/*
** pf_itoa_base ()
** без знака длинная длинная максимальная: 18,446,744,073,709,551,615 (26 танков + 1 '\ 0')
** Таким образом, буфер из 27 char-ов является самым большим, что мы когда-либо должны были рассмотреть.
**
** Поскольку '+' / '-' / '' обрабатываются в функции handle_prepad (), мы не
** нужно беспокоиться о них и просто сосредоточиться на цифрах.
*/

void        pf_itoa_base(t_vfpf *p, uintmax_t nbr, int nbr_len)
{
    char    res[27];
    int     tmp_len;
    int     len_diff;
    int     base;
    char    char_case;

    base = p->base;
    char_case = ('a' - 10 - (('a' - 'A') * UPPER(p->specifier)));
    tmp_len = nbr_len;
    while (tmp_len--)
    {
        len_diff = nbr_len - tmp_len;
        if (p->flags & APOST_FLAG && len_diff % 4 == 0 && len_diff > 0)
            res[tmp_len] = ',';
        else
        {
            res[tmp_len] = (nbr % base) + ((nbr % base < 10) ? '0' : char_case);
            nbr /= base;
        }
    }
    buff(p, res, nbr_len);
}


/*
** handle_prepend ()
** Запишите "-" / "+" / "" "по мере необходимости.
** ПРИМЕЧАНИЕ: "-" имеет приоритет перед "+", которые оба имеют приоритет перед ""
** ПРИМЕЧАНИЕ2: "-" / "+" / "" игнорируются для неподписанных целых
*/

static void     handle_prepend(t_vfpf *p, singed_int)
{
    int     spec;

    spec = p->specifier;
}