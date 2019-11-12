/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:33:29 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:33:32 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_splitdel(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	if (split)
	{
		str = *split;
		while (*str)
		{
			ft_strdel(str);
			i++;
			str = &(*split)[i];
		}
		ft_memdel((void **)split);
	}
}
