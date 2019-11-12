/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:39:34 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:39:36 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strnew(size_t size)
{
	char	*new_str;

	new_str = NULL;
	new_str = (char *)malloc((size + 1) * sizeof(char));
	if (new_str)
		ft_memset(new_str, '\0', size + 1);
	return (new_str);
}
