/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:26:46 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/08/16 16:00:41 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_all_variable *data)
{
	if (data->file1 != -1)
		close(data->file1);
	if (data->file2 != -1)
		close(data->file2);
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close(data->pipefd[1]);
}

void	ft_quit(char *str, int i, t_all_variable *data)
{
	if (errno)
	{
		perror(str);
		errno = 0;
	}
	else
	{
		ft_putstr_fd(str, 2);
	}
	if (i == 0)
	{
		close_fd(data);
		exit(EXIT_FAILURE);
	}
}

void	enfant1(char **av, t_all_variable *data, char **envp)
{
	char	*tmp;

	tmp = ft_prepare_to_split(av[2], 0);
	data->cmd1 = ft_split(tmp, 001);
	data->path1 = get_exec(data->cmd1, envp, 0);
	if (data->path1 == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (!data->cmd1[0])
			write(2, "\n", 1);
		ft_putendl_fd(data->cmd1[0], 2);
		ft_free(data->cmd1, data->path1, 0); 
		exit(EXIT_FAILURE);
	}
	dup2(data->file1, STDIN_FILENO);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close_fd(data);
	execve(data->path1, data->cmd1, envp);
}

void	enfant2(char **av, t_all_variable *data, char **envp)
{
	char	*tmp;

	tmp = ft_prepare_to_split(av[3], 0);
	data->cmd2 = ft_split(tmp, 001);
	data->path2 = get_exec(data->cmd2, envp, 0);
	if (data->path2 == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(data->cmd2[0], 2);
		ft_free(data->cmd2, data->path2, 0);
		exit(EXIT_FAILURE);
	}
	dup2(data->pipefd[0], STDIN_FILENO);
	dup2(data->file2, STDOUT_FILENO);
	close_fd(data);
	execve(data->path2, data->cmd2, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_all_variable	data;

	if (ac != 5)
		ft_quit("model : /pipex file1 cmd1 cmd2 file2\n", 0, &data);
	data.file1 = open(av[1], 'r');
	if (data.file1 == -1)
		ft_quit(av[1], 1, &data);
	data.file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.file2 == -1)
		ft_quit(av[4], 0, &data);
	if (pipe(data.pipefd) == -1)
		ft_quit("Error with initialisation of pipe fd \n", 0, &data);
	if (data.file1 != -1)
		data.pid1 = fork();
	if (!data.pid1)
		enfant1(av, &data, envp);
	data.pid2 = fork();
	if (!data.pid2)
		enfant2(av, &data, envp);
	close_fd(&data);
	if (data.file1 != -1)
		waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	return (0);
}
