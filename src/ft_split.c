/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:27:11 by awooden           #+#    #+#             */
/*   Updated: 2022/03/23 17:47:12 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
	int	find_word_end(char const *s, char del, int pos)
{
	pos++;
	while (s[pos] != del && s[pos])
		pos++;
	return (pos);
}

static
	int	calc_word_count(char const *s, char del)
{
	int	pos;
	int	res;

	pos = 0;
	res = 0;
	while (s[pos])
	{
		if (s[pos] != del)
		{
			pos = find_word_end(s, del, pos);
			res++;
		}
		else
			pos++;
	}
	return (res);
}

static
	char	*add_word(char const *s, int pos, int fwe_pos)
{
	int		word_len;
	char	*res;
	int		i;

	word_len = fwe_pos - pos;
	res = malloc(sizeof(char) * (word_len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (pos < fwe_pos)
		res[i++] = s[pos++];
	res[i] = '\0';
	return (res);
}

static
	int	handle_bad_malloc(char **str_arr, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		while (str_arr[i] != NULL)
			free(str_arr[i++]);
		free(str_arr);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		pos;
	int		i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (calc_word_count(s, c) + 1));
	if (res == NULL)
		return (NULL);
	pos = 0;
	i = 0;
	while (s[pos])
	{
		if (s[pos] != c)
		{
			res[i++] = add_word(s, pos, find_word_end(s, c, pos));
			if (handle_bad_malloc(res, res[i - 1]))
				return (res);
			pos = find_word_end(s, c, pos);
		}
		else
			pos++;
	}
	res[i] = NULL;
	return (res);
}
