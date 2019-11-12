/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:36:36 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:36:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*new_s1;
	char	*start;
	size_t	len;

	len = ft_strlen(s1);
	new_s1 = (char *)malloc((len + 1) * sizeof(*new_s1));
	if (new_s1)
	{
		new_s1[len] = '\0';
		start = new_s1;
		while (len--)
		{
			*new_s1++ = *s1++;
		}
		return (start);
	}
	return (NULL);
}
