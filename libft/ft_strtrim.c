/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:40:46 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:42:43 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

/*
** Если мы получим пустую строку или только строку пробелов, то мы хотим
** вернуть пустую строку. Мы возвращаем ft_strdup (""), потому что обычно
** malloc'd «отделка» будет освобожден в какой-то момент. Если бы мы только вернулись
**	вернуть(""); тогда попытка освободить константный символ закончится плохо.
**
** (s || (trim = NULL)) - глупый уродливый хак, потому что, очевидно, если вы
** хочу функцию безопасности, а также хочу функцию до 25 строк, очень плохо ...
** Часть (trim = NULL) всегда будет иметь значение «false». Если 's' не существует
** затем мы возвращаем тримминг, который мы присвоили NULL. Если 's' существует
** тогда отлично, правда || False '(т. Е. S || (trim = NULL)') также становится истинным ...
*/

static int	is_wspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	const char		*strt;
	const char		*end;
	char			*trim;
	char			*tmp;

	if (s || (trim = NULL))
	{
		while (is_wspace(*s))
			s++;
		if (*(strt = s) == '\0')
			return (ft_strdup(""));
		while (*s)
			s++;
		while (is_wspace(*s) || *s == '\0')
			s--;
		end = ++s;
		if ((trim = (char *)malloc(((end - strt) + 1) * sizeof(*trim))))
		{
			tmp = trim;
			while (end - strt != 0)
				*tmp++ = *strt++;
			*tmp = '\0';
		}
	}
	return (trim);
}
