/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:35:35 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:35:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char *cs1;
	unsigned char *cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (*cs1 == *cs2)
	{
		if (*cs1 == '\0')
			return (0);
		cs1++;
		cs2++;
	}
	return ((int)(*cs1 - *cs2));
}
