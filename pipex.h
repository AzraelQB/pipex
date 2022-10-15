/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:27:23 by awooden           #+#    #+#             */
/*   Updated: 2022/10/15 15:46:33 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_fds
{
	int	in;
	int	out;
	int	**pipes;
}	t_fds;

size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strnfind(char *str, char **str_arr, int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
void		pserror(char *error_text);
char		**ft_split(char const *s, char c);
void		free_arr(char **arr);
int			ft_arrlen(char	**strarr);
char		*get_next_line(int fd);
t_fds		*create_t_fds(int cmdc);
t_fds		*init_fds(t_fds *pipexfds, int i, int cmdc, char **argv);
void		free_t_fds(t_fds *pipexfds);
char		*get_cmd_path(char **paths, char *cmd);
char		**get_paths(char **env);
char		*make_cmd(char **env, char *cmd);
t_fds		*read_stdin(char **argv, t_fds *pipexfds);
void		child(char *str, char **env, t_fds *pipexfds);
void		end_parent(t_fds *pipexfds, pid_t *pids, int cmdc);

#endif