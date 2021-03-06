/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:35:46 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:37:29 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Более подробный, но эквивалентный метод будет:
** while ((* dest ++ = * src ++)! = '\ 0')
*/

char	*ft_strcpy(char *dest, char *src)
{
	char *dest_start;

	dest_start = dest;
	while ((*dest++ = *src++))
		;
	return (dest_start);
}
