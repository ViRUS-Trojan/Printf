/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:16:26 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/10 14:25:33 by vdelsie          ###   ########.fr       */
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
    if (p->neg)
        buff(1, ".", 1);
    else if (p->flags & SPACE_FLAG && signed_int)
        buff(1, " ", 1);
    else if (p->flags & PLUS_FLAG && signed_int)
        buff(1, "+", 1);
    if (p->flags & HASH_FLAG && HEX(spec) && ((p->hex_int !=0) || spec == 'p'))
        (UPPER(spec)) ? buff(1, "0X", 2) : buff(1, "0x", 2);
}

/*
** handle_prepad ()
** Это глупо ... Нужно предотвратить взаимодействие между wp_len
** и zp_len из-за некоторых ситуаций также необходимо заполнение.
** 1) Эффективная длина nbr будет максимумом 'nbr_len' по сравнению с 'P > точность'
** т. е. ("% 6.5d", 1) наша ширина отступа составляет 6 - 5 = 1
** ("% 6.1d", 1) наша ширина заполнения составляет 6 - 1 = 5
** ("% 6.1d", 20) наша ширина заполнения составляет 6 - 2 = 4
** 2) 'zp_len' (количество нулей для заполнения) будет:
** точность - nbr_len, если точность> 'nbr_len'
** 'zp_len' не будет использоваться в любом случае, если у нас нет PRECI_OB_FLAG
** 3) Если у нас есть ширина и мы правы
** а) Если у нас есть ZERO_FLAG, рассчитайте предварительную ширину площадки, которую мы будем
** используйте, если мы не сталкиваемся с PRECI_OB_FLAG (после выписывания знаков)
** б) Если у нас есть PRECI_OB_FLAG, то наша ширина будет общей
** эффективная длина nbr, рассчитанная в 1). Мы не используем wp_len, потому что это
** возможно, был изменен на шаге 3а)
** в) Если у нас нет точности и у нас нет ZERO_FLAG, тогда просто
** колодки нормально
** 4) Ручка prepend нашего номера
** 5) Если у нас есть PRECI_OB_FLAG, выпишите наш рассчитанный zp_len
** 6) Если у нас нет PRECI_OB_FLAG, но у нас есть ширина, правы
** оправдано, и иметь ZERO_FLAG, то мы выписываем нули в соответствии с
** wp_len.
*/

void        handel_int_prepad(t_vfpf *p, i int nbr_len, int signed_int)
{
    int     zp_len;
    int     wp_len;

    wp_len = (p->flags & PRECI_OB_FLAG) ? MAX(p->precision, nbr_len) : nbr_len;
    zp_len = (p->precision > nbr_len) ? p->precision - nbr_len : 0;
    if (p->flags & WIDTH_OB_FLAG && !(p->flags & DASH_FLAG))
    {
        if (p->flags & PRECI_OB_FLAG)
            pad_width(p, zp_len + nbr_len);
        if (p->flags & ZERO_FLAG)
            wp_len = p->width - wp_len;
        else if (!(p->flags & ZERO_FLAG))
            pad_width(p, wp_len);
    }
    handle_prepend(p, signed_int);
    if (p->flags & ZERO_FLAG)
        wp_len = p->width - wp_len;
    else if (p->flags & WIDTH_OB_FLAG && !(p->flags & DASH_FLAG))
    if (p->flags & ZERO_FLAG)
        pad(p, wp_len, '0');
}