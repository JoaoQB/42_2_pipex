/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/24 10:32:54 by jqueijo-         ###   ########.fr       */
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

static int		i;

void	execute(char *argv, char **envp)
{
	char	**command;
	// char	*full_command;
	// size_t	len;
	// char	cmd_path;

	command = ft_split(argv, ' ');
	if (!command)
		ft_error("");
	// len = ft_strlen(*command);
	// ft_strlcpy(full_command, *command, len + 1);
	// while (*++command)
	while(*command)
	{
		// full_command = ft_strjoin(full_command, *command);
		printf("Command is %s, printed for the %dth time\n", *command, i++);
		command++;
	}
	// ft_free_doublearray(command);
	// free(command);
	// printf("Full Command is %s, printed for the %dth time\n", full_command, i++);
}
