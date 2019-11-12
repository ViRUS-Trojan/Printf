/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:13 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:38:16 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	char	*temp;
	size_t	new_len;

	if (s1 && s2)
	{
		new_len = ft_strlen(s1) + ft_strlen(s2);
		join_str = NULL;
		join_str = (char *)malloc((new_len + 1) * sizeof(*join_str));
		if (join_str)
		{
			temp = join_str;
			while (*s1)
				*temp++ = *s1++;
			while (*s2)
				*temp++ = *s2++;
			*temp = '\0';
		}
		return (join_str);
	}
	return (NULL);
}
