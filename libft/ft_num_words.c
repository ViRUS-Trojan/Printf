/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:31:57 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:31:59 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_num_words(const char *str, char sep)
{
	size_t	num_words;

	num_words = 0;
	while (*str == sep)
		str++;
	while (*str != '\0')
	{
		str++;
		if (*str == sep)
		{
			num_words++;
			while (*str == sep)
				str++;
		}
	}
	if (!(*(str - 1) == sep) && *(str - 1))
		num_words++;
	return (num_words);
}
