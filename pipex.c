/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:11:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/31 12:46:42 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file(int argc, char **argv, int *fd, int file_nbr)
{
	if (file_nbr == 1)
	{
		*fd = open(argv[1], O_RDONLY);
		if (*fd == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		*fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (*fd == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		dup2(*fd, STDOUT_FILENO);
		close(*fd);
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

/*  valgrind --leak-check=yes --track-origins=yes
 --track-fds=yes --trace-children=yes */
int	main(int argc, char **argv, char **envp)
{
	int	input_file;
	int	output_file;
	int	i;

	i = 2;
	if (argc >= 5)
	{
		open_file(argc, argv, &input_file, 1);
		while (i < (argc - 2))
			pipex(argv[i++], envp);
		open_file(argc, argv, &output_file, 2);
		execute(argv[i], envp);
	}
	else
	{
		write(2, "Not enough parameters\n", 23);
		exit(EXIT_FAILURE);
	}
}
