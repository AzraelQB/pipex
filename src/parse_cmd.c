/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:32:54 by awooden           #+#    #+#             */
/*   Updated: 2022/03/23 18:13:26 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*res;

	while (*paths)
	{
		res = ft_strjoin(*paths, cmd);
		if (!res)
			pserror("Error: bad malloc (ft_strjoin paths cmd)");
		if (access(res, X_OK) == -1)
		{
			free(res);
			paths++;
		}
		else
			return (res);
	}
	pserror("Error: can't access the command given");
	return (res);
}

char	**get_paths(char **env)
{
	int		paths_ind;
	char	*tmp;
	char	**paths;

	paths_ind = ft_strnfind("PATH=", env, 5);
	if (paths_ind == 0)
		pserror("Error: no PATH in env");
	tmp = *(env + paths_ind) + 5;
	paths = ft_split(tmp, ':');
	if (!paths)
		pserror("Error: bad malloc (ft_split paths)");
	return (paths);
}

char	*make_cmd(char **env, char *cmd)
{
	char	*res;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		pserror("Error: bad malloc (ft_strjoin '/' cmd)");
	paths = get_paths(env);
	res = get_cmd_path(paths, cmd);
	free_arr(paths);
	free(cmd);
	return (res);
}
