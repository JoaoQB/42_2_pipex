/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:11:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/29 13:01:50 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int argc, char **argv, int *fd_in, int *fd_out)
{
	if (ft_strcmp(argv[1], "here_doc") != 0)
	{
		*fd_in = open(argv[1], O_RDONLY);
		*fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (*fd_in == -1 || *fd_out == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(*fd_in, STDIN_FILENO);
			close(*fd_in);
		}
	}
	else
	{
		*fd_out = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC, 0644);
		if (*fd_out == -1)
			perror("Error in open_files\n");
		//dup2() terminal -> stdin_fileno;
	}
}

void	child_process(int *pipe_end, char *argv, char **envp)
{
	close(pipe_end[0]);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	execute(argv, envp);
}

void	parent_process(int *pipe_end)
{
	waitpid(0, NULL, 0);
	close(pipe_end[1]);
	dup2(pipe_end[0], STDIN_FILENO);
	close(pipe_end[0]);
}

void	pipex(char *argv, char **envp)
{
	int		pipe_end[2];
	pid_t	process_id;

	if (pipe(pipe_end) < 0)
		perror("");
	process_id = fork();
	if (process_id < 0)
		perror("");
	if (process_id == 0)
		child_process(pipe_end, argv, envp);
	else
		parent_process(pipe_end);
}

int	main(int argc, char **argv, char **envp)
{
	int	input_file;
	int	output_file;
	int	i;

	i = 2;
	if (argc >= 5)
	{
		open_files(argc, argv, &input_file, &output_file);
		while (i < (argc - 2))
		{
			if (ft_strcmp(argv[1], "here_doc") != 0)
				pipex(argv[i++], envp);
			else
			{
				i = 3;
				pipex(argv[i++], envp);
			}
		}
		dup2(output_file, STDOUT_FILENO);
		close(output_file);
		execute(argv[argc - 2], envp);
	}
}
