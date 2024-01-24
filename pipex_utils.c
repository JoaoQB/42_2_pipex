/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/23 14:54:42 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *string)
{
	perror(string);
	// exit(EXIT_FAILURE);
}

static int		i;

void	execute(char *argv, char **envp)
{
	char	**command;

	// char	cmd_path;

	command = ft_split(argv, ' ');
	if (!command)
		ft_error("");
	// while (*command)
	// {
		printf("Command is %s, printed for the %dth time\n", *command, i++);
	// 	command++;
	// }
}
