/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:05:32 by awooden           #+#    #+#             */
/*   Updated: 2022/03/23 18:47:03 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *str, char **env, t_fds *pipexfds)
{
	char	**cmd_flags;
	char	*cmd_no_flags;
	int		i;

	cmd_flags = ft_split(str, ' ');
	if (!cmd_flags)
		pserror("Error: bad malloc (ft_split cmd)");
	cmd_no_flags = make_cmd(env, cmd_flags[0]);
	dup2(pipexfds->in, 0);
	dup2(pipexfds->out, 1);
	i = -1;
	while (pipexfds->pipes[++i])
	{
		if (close(pipexfds->pipes[i][0]) || close(pipexfds->pipes[i][1]))
			write(2, "Warning: failed to close pipe fd\n", 33);
	}
	execve(cmd_no_flags, cmd_flags, NULL);
	free_arr(cmd_flags);
	free(cmd_no_flags);
	free_t_fds(pipexfds);
	pserror("Error: execve mistake");
}

t_fds	*read_stdin(char **argv, t_fds *pipexfds)
{
	char	*str;
	int		file;

	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file == -1)
		pserror("Error: can't form a here_doc");
	while (1)
	{
		str = get_next_line(0);
		if (!str)
			pserror("Error: reading stdin mistake");
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0 && \
				str[ft_strlen(argv[2])] == '\n')
			break ;
		write(file, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(file);
	pipexfds->in = open(".heredoc", O_RDONLY);
	if (pipexfds->in == -1)
		pserror("Error: can't open a here_doc");
	pipexfds->out = pipexfds->pipes[1][1];
	return (pipexfds);
}

void	end_parent(t_fds *pipexfds, pid_t *pids, int cmdc)
{
	int	i;

	i = -1;
	while (pipexfds->pipes[++i])
	{
		if (close(pipexfds->pipes[i][0]) || close(pipexfds->pipes[i][1]))
			write(2, "Warning: failed to close pipe fd\n", 33);
	}
	i = -1;
	while (++i < cmdc)
		waitpid(pids[i], NULL, 0);
	if (open(".heredoc", O_RDONLY) != -1)
		unlink(".heredoc");
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	pid_t	*pids;
	t_fds	*pipexfds;

	if (!env || argc < 5)
		pserror("Error: arguments mistake");
	pipexfds = create_t_fds(argc - 3);
	pids = malloc(sizeof(pid_t) * argc);
	i = -1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		++i;
	while (++i < argc - 3)
	{
		pipexfds = init_fds(pipexfds, i, argc - 3, argv);
		pids[i] = fork();
		if (pids[i] == -1)
			pserror("Error: fork mistake");
		if (pids[i] == 0)
			child(argv[i + 2], env, pipexfds);
	}
	end_parent(pipexfds, pids, argc - 3);
	free_t_fds(pipexfds);
	free(pids);
	return (0);
}

	// char	**ar;

	// ar = malloc(1000);
	// ar[0] = ft_strdup("./a.out");
	// ar[1] = ft_strdup("infile");
	// ar[2] = ft_strdup("1");
	// ar[3] = ft_strdup("2");
	// ar[4] = ft_strdup("outfile");
	// argc = 5;

	// free_arr(ar);
