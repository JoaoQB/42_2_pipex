/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/18 18:51:34 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *string)
{
	perror(string);
	// exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**command;
	// char	cmd_path;

	command = ft_split(argv, ' ');
	if (!command)
		ft_error("");
	while (*command)
	{
		printf("Command is %s\n", *command);
		*command++;
	}
}
