/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:14:11 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:14:13 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int		itoa_len(int num, int base)
{
	int count;

	count = 0;
	while (num != 0)
	{
		num = num / base;
		count++;
	}
	return (count);
}

char			*ft_itoa(int nbr)
{
	char	*result;
	int		len;
	int		ind;

	ind = 0;
	len = itoa_len(nbr, 10);
	if (nbr < 0)
		len = len + 1;
	if (nbr == 0)
		len = 1;
	result = NULL;
	if ((result = (char *)malloc(sizeof(*result) * (len + 1))))
	{
		if (nbr < 0)
			result[0] = '-';
		if (nbr == 0)
			result[0] = '0';
		while (nbr != 0)
		{
			result[(len - ind++) - 1] = ft_abs(nbr % 10) + '0';
			nbr = nbr / 10;
		}
		result[len] = '\0';
	}
	return (result);
}
