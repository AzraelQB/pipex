/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:30:44 by awooden           #+#    #+#             */
/*   Updated: 2022/03/23 18:38:52 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	}
	if ((char)c == 0)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*res;

	len = 0;
	while (s1[len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = 0;
	while (--len >= 0)
		res[len] = s1[len];
	return (res);
}

void	pserror(char *error_text)
{
	write(2, error_text, ft_strlen(error_text));
	write(2, "\n", 1);
	if (open(".heredoc", O_RDONLY) != -1)
		unlink(".heredoc");
	exit(1);
}

void	free_arr(char **arr)
{
	char	*cur;
	int		i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		cur = arr[i];
		i++;
		free(cur);
	}
	free(arr);
}

int	ft_arrlen(char	**strarr)
{
	int	res;

	res = 0;
	if (strarr == NULL)
		return (0);
	while (*strarr)
	{
		res++;
		strarr++;
	}
	return (res);
}
