/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:40:01 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/07/22 18:11:35 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_all_variable
{
	int		file1;
	int		file2;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}			t_all_variable;

char	**get_path(char **envp, int i);
char	*get_exec(char **cmd, char **envp, int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_quit(char *str, int i, t_all_variable *data);
void	ft_free(char **tab, char *str, int i);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putchar_fd(char c, int fd);
char	*ft_prepare_to_split(char *s1, int i);

#endif