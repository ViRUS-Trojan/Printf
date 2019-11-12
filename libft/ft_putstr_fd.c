/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:33:12 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:33:13 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
	}
}
