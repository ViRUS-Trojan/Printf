/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:30:56 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:31:33 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>


/*
** memmove проверяет, перекрываются ли dst и src
** Если наша dst больше, чем source + 'len to copy', мы можем просто
** слепо копировать вперед как с memcpy.
**
** Однако, если наша dst короче, чем source + 'len to copy', тогда
** мы должны копировать с конца (то есть с dst + len обратно на dst).
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *end;
	unsigned char *src_ptr;
	unsigned char *dst_ptr;

	if ((size_t)dst - (size_t)src >= len)
		return (ft_memcpy(dst, src, len));
	else
	{
		end = (unsigned char *)dst;
		src_ptr = (unsigned char *)src + len;
		dst_ptr = (unsigned char *)dst + len;
		while (dst_ptr != end)
			*--dst_ptr = *--src_ptr;
	}
	return (dst);
}
