/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:11:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/11 18:17:05 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int argc, char **argv, int *fd_in, int *fd_out)
{
	*fd_in = open(argv[1], O_RDONLY);
	*fd_out = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC | 0644);
	if (*fd_in == -1 || *fd_out == -1)
		ft_error("Error in open_files\n");
	else
		printf("Opened files successfully\n");
}

void	pipex(int *fd_in, int *fd_out, char **argv, char **envp)
{

}

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (argc >= 5)
	{
		if (argv[1] != "here_doc")
			open_files(argc, argv, &fd_in, &fd_out);
		// else
		// 	here_doc()
		pipex(&fd_in, &fd_out, **argv, **envp);
	}
}
