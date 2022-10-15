/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:05:07 by awooden           #+#    #+#             */
/*   Updated: 2022/03/23 18:41:01 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_fds	*create_t_fds(int cmdc)
{
	t_fds	*res;
	int		i;

	i = -1;
	res = malloc(sizeof(t_fds));
	res->pipes = malloc(sizeof(int *) * (cmdc));
	while (++i < (cmdc - 1))
		res->pipes[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < (cmdc - 1))
	{
		if (pipe(res->pipes[i]) == -1)
			pserror("Error: pipe mistake");
	}
	res->pipes[i] = NULL;
	return (res);
}

t_fds	*init_fds(t_fds *pipexfds, int i, int cmdc, char **argv)
{
	if (i == 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipexfds = read_stdin(argv, pipexfds);
	else if (i == 0)
	{
		pipexfds->in = open(argv[1], O_RDONLY);
		if (pipexfds->in == -1)
			pserror("Error: can't open");
		pipexfds->out = pipexfds->pipes[0][1];
	}
	else if (i == cmdc - 1)
	{
		pipexfds->in = pipexfds->pipes[i - 1][0];
		pipexfds->out = open(argv[ft_arrlen(argv) - 1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipexfds->out == -1)
			pserror("Error: can't open");
	}
	else
	{
		pipexfds->in = pipexfds->pipes[i - 1][0];
		pipexfds->out = pipexfds->pipes[i][1];
	}
	return (pipexfds);
}

void	free_t_fds(t_fds *pipexfds)
{
	int	i;

	i = -1;
	while (pipexfds->pipes[++i])
		free(pipexfds->pipes[i]);
	free(pipexfds->pipes);
	free(pipexfds);
}
