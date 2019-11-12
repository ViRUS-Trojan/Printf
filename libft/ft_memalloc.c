/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:29:02 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:29:04 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void *new_mem;

	if (!(new_mem = malloc(size)))
		return (NULL);
	ft_bzero(new_mem, size);
	return (new_mem);
}
