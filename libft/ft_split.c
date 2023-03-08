/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imendonc <imendonc@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:31:15 by imendonc          #+#    #+#             */
/*   Updated: 2023/01/18 18:43:03 by imendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contador(char const *s, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*duplicador(char const *str, int strt, int end)
{
	char	*palavra;
	int		i;

	i = 0;
	palavra = malloc(((end - strt) + 1) * sizeof(char));
	if (!palavra)
		return (0);
	while (strt < end)
		palavra[i++] = str[strt++];
	palavra[i] = '\0';
	return (palavra);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	int		f;
	size_t	index;

	f = 0;
	i = 0;
	split = malloc((contador(s, c) + 1) * sizeof(char *));
	index = 0;
	if (!s || !split)
		return (NULL);
	while (i < ft_strlen(s))
	{
		while (s[i] == c)
			i++;
		index = i;
		while (s[i] != c && s[i])
			i++;
		if (s[i] || i > index)
			split[f++] = duplicador(s, index, i);
	}
	split[f] = NULL;
	return (split);
}
