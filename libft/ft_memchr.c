/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:29:41 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:29:44 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *src_ptr;

	src_ptr = (unsigned char *)s;
	while (n--)
	{
		if (*src_ptr == (unsigned char)c)
			return (src_ptr);
		src_ptr++;
	}
	return (NULL);
}
