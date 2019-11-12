/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:20:10 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:20:26 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_lstlen(t_list *begin_list)
{
	size_t	count;

	count = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		count++;
	}
	return (count);
}
