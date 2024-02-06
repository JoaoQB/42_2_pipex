/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/06 16:13:21 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
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

	paths = NULL;
	if (*envp)
	{
		while (*envp)
		{
			if (ft_strnstr(*envp, "PATH=", 5))
				break ;
			envp++;
		}
		paths = *envp;
	}
	if (!paths)
		paths = ft_strdup("no_paths");
	while (*paths != '/' && *paths)
		paths++;
	command_paths = ft_split(paths, ':');
	return (command_paths);
}

char	*check_paths(char **possible_paths, char *command)
{
	char	*cmd_path;
	int		fd;

	while (*possible_paths)
	{
		cmd_path = ft_strjoin(*possible_paths, command);
		fd = access(cmd_path, F_OK);
		if (fd == 0)
			return (cmd_path);
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
	int		i;

	command = ft_split(argv, ' ');
	possible_paths = get_paths(envp);
	i = 0;
	if (!command)
		perror("");
	command_path = check_paths(possible_paths, *command);
	if (!command_path)
	{
		write(2, "command not found: ", 20);
		while (argv[i])
			write(2, &argv[i++], 1);
		write(2, "\n", 1);
	}
	else
		execve(command_path, command, envp);
	free(command_path);
	ft_free_doublearray(command);
	ft_free_doublearray(possible_paths);
	exit(EXIT_FAILURE);
}
