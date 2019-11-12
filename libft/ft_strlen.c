/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:36 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:38:37 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlen(const char *str)
{
	const char *str_adv;

	str_adv = str;
	while (*str_adv != '\0')
		str_adv++;
	return (str_adv - str);
}
