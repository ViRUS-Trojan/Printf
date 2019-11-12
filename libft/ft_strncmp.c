/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:39:10 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:39:11 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned char *cs1;
	unsigned char *cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	if (n)
	{
		while ((*cs1 == *cs2) && --n)
		{
			if (*cs1 == '\0')
			{
				return (0);
			}
			cs1++;
			cs2++;
		}
		return ((int)(*cs1 - *cs2));
	}
	return (0);
}
