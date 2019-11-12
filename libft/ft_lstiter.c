/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:16:04 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:16:05 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *curr_elem;

	curr_elem = lst;
	while (curr_elem)
	{
		(*f)(curr_elem);
		curr_elem = curr_elem->next;
	}
}
