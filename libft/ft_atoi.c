/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:12:11 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:12:13 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		is_spacer(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v')
	{
		return (1);
	}
	if (c == '\f')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int				ft_atoi(char *str)
{
	int result;
	int sign;

	result = 0;
	sign = -1;
	while (is_spacer(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result *= 10;
		result -= *str - '0';
		str++;
	}
	return (sign * result);
}
