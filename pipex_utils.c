/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:57 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/17 11:33:36 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *string)
{
	perror(string);
	// exit(EXIT_FAILURE);
}

// void	execute(char **argv, char **envp)
// {

// }
