/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:15:41 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:15:43 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	if (alst && del)
	{
		while (*alst)
		{
			next = (*alst)->next;
			(*del)((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = next;
		}
	}
}
