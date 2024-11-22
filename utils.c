/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:10:36 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/07/18 14:36:34 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **tab, char *str, int i)
{
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	if (str)
		free(str);
}

char	**get_path(char **envp, int i)
{
	char	**bigpath;

	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			bigpath = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':');
		}
		i++;
	}
	return (bigpath);
}

char	*get_exec(char **cmd, char **envp, int i)
{
	char	**bigpath;
	char	*tmp;
	char	*executable;

	if (access(cmd[0], X_OK) != -1)
		return (cmd[0]);
	if (!envp[0])
		return (NULL);
	bigpath = get_path(envp, 0);
	while (bigpath && bigpath[i])
	{
		tmp = ft_strjoin(bigpath[i], "/");
		executable = ft_strjoin(tmp, cmd[0]);
		if (access(executable, X_OK) != -1)
		{
			ft_free(bigpath, tmp, 0);
			return (executable);
		}
		free(tmp);
		free(executable);
		i++;
	}
	ft_free(bigpath, NULL, 0);
	return (NULL);
}

char	*ft_prepare_to_split(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	if ((count % 2) == 1)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != 39)
	{
		if (str[i] == 32)
			str[i] = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] == 39)
			str[i] = 1;
		i++;
	}
	return (str);
}
