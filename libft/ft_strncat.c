/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:39:01 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:39:02 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *dest, char *src, int nb)
{
	int dest_len;
	int src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (src_len < nb)
		ft_strcpy(&dest[dest_len], src);
	else
	{
		ft_strncpy(&dest[dest_len], src, nb);
		dest[dest_len + nb] = '\0';
	}
	return (dest);
}
