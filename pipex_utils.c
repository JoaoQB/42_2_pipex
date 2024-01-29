/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/29 12:46:28 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *string)
{
	perror(string);
	// exit(EXIT_FAILURE);
}

void	ft_free_doublearray(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**get_paths(char **envp)
{
	char	**command_paths;
	char	*paths;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	paths = *envp;
	while (*paths != '/')
		paths++;
	command_paths = ft_split(paths, ':');
	return (command_paths);
}

char	*check_paths(char **possible_paths, char *command)
{
	char	*cmd_path;
	int		fd;

	while(*possible_paths)
	{
		cmd_path = ft_strjoin(*possible_paths, command);
		fd = access(cmd_path, F_OK);
		if (fd == 0)
			return(cmd_path);
		possible_paths++;
		free(cmd_path);
	}
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**command;
	char	**possible_paths;
	char	*command_path;

	command = ft_split(argv, ' ');
	possible_paths = get_paths(envp);
	if (!command)
		ft_error("");
	command_path = check_paths(possible_paths, *command);
	if (!command_path)
		ft_error("command not found");
	else
		execve(command_path, command, envp);
	write(2, "reached cleaning child\n", 24);
	free(command_path);
	ft_free_doublearray(command);
	ft_free_doublearray(possible_paths);
	write(2, "finished cleaning\n", 19);
}
