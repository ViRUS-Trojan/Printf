/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:40:12 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:40:13 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	const char *last_match;

	last_match = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_match = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (last_match)
		return ((char *)last_match);
	return (NULL);
}
