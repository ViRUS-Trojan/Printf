/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:29:10 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:29:11 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <libft.h>

/*
**	First assign value of src_ptr to dst_ptr then check if dst_ptr == c
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst_ptr;
	unsigned char *src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	while (n--)
	{
		if ((*dst_ptr++ = *src_ptr++) == (unsigned char)c)
			return (dst_ptr);
	}
	return (NULL);
}
