/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:53 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:38:55 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map_str;
	char			*start;
	unsigned int	len;
	unsigned int	ind;

	if (s && (*f))
	{
		len = (unsigned int)ft_strlen(s);
		ind = 0;
		map_str = (char *)malloc((len + 1) * sizeof(*map_str));
		if (map_str)
		{
			map_str[len] = '\0';
			start = map_str;
			while (ind < len)
			{
				*map_str++ = (*f)(ind++, *s++);
			}
			return (start);
		}
	}
	return (NULL);
}
