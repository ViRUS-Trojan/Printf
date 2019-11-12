/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:30:36 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:30:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_memdup(void const *src, size_t size)
{
	void *dup;

	if (!(dup = malloc(size)))
		return (NULL);
	ft_memcpy(dup, src, size);
	return (dup);
}
