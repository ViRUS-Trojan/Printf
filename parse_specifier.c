/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:41:48 by vdelsie           #+#    #+#             */
/*   Updated: 2019/12/07 20:10:49 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

/*
** ft_printf должен минимально обрабатывать s S p d D i o U u x X c C
** Настройка таблицы переходов, в которой содержатся заданные позиции ascii (int)
** адреса обработчиков функций.
*/

static void     setup_jump_tabled(t_jumptable, j_table[128])
{
    j_table['n'] = &handle_n;
    j_table['p'] = &handle_unsingers_hex;
    j_table['s'] = &handle_str;
    j_table['S'] = &handle_str;
    j_table['c'] = &handle_char;
    j_table['C'] = &handle_char;
    j_table['a'] = &handle_double_hex;
    j_table['A'] = &handle_double_hex;
    j_table['g'] = &handle_double_shortest;
    j_table['G'] = &handle_double_shortest;
    j_table['e'] = &handle_double_sci;
    j_table['E'] = &handle_double_sci;
    j_table['f'] = &handle_double;
    j_table['F'] = &handle_double;
    j_table['x'] = &handle_unsignet_int_hex;
    j_table['X'] = &handle_unsignet_int_hex;
    j_table['u'] = &handle_unsignet_int_dec;
    j_table['U'] = &handle_unsignet_int_dec;
    j_table['o'] = &handle_unsignet_int_oct;
    j_table['O'] = &handle_unsignet_int_oct;
    j_table['i'] = &handle_int;
    j_table['d'] = &handle_int;
    j_table['D'] = &handle_int;
    j_table['%'] = &handle_escape;
}


/*
** get_func () - настроить таблицу переходов, чтобы мы могли получить соответствующую функцию
** для любого заданного спецификатора, который мы находим.
**
** Мы делаем нашу статическую перемычку статической, поэтому нам нужно распечатать
** и задайте ему размер 127 + 1 (максимальное значение для символа ascii)
**
** Нам нужно защитить нашу таблицу прыжков, убедившись, что наш символ
** ASCII.
*/

t_jumptable     get_handler_funct(char c)
{
    static t_jumptable      specifier_jt[128] = {NULL};

    if (specifier_jt['%'] == NULL)
        setup_jump_tabled(specifier_jt);
    if (ft_isascii(c))
		return (specifier_jt[(int)c]);
	else
		return (NULL);
}