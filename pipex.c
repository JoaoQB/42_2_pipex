/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:11:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/17 14:17:51 by jqueijo-         ###   ########.fr       */
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
			ft_error("Error in open_files\n");
		else
			printf("Opened files successfully\n");
		dup2(*fd_in, STDIN_FILENO);
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_in);
		close(*fd_out);
	}
	else
	{
		*fd_out = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC, 0644);
		if (*fd_out == -1)
			ft_error("Error in open_files\n");
		else
			printf("Opened files successfully\n");
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
}

void	child_process(int *pipe_end, char **argv, char **envp)
{
	close(pipe_end[0]);
	printf("wrote successfully\n");
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	write(1, "wrote successfully\n", 19);
	// execute(argv, envp);
}

void	parent_process(int *pipe_end, char **argv, char **envp)
{
	wait(NULL);
	close(pipe_end[1]);
	dup2(pipe_end[0], STDIN_FILENO);
	close(pipe_end[0]);
	write(1, "read successfully\n", 18);
}

void	pipex(char **argv, char **envp)
{
	int		pipe_end[2];
	pid_t	process_id;

	if (pipe(pipe_end) < 0)
		ft_error("Pipe error\n");
	else
		printf("Piped Sucessfully\n");
	process_id = fork();
	if (process_id < 0)
		ft_error("Fork error\n");
	else
		printf("Forked Successfully\n");
	if (process_id == 0)
		child_process(pipe_end, argv, envp);
	else
		parent_process(pipe_end, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	input_file;
	int	output_file;

	if (argc >= 5)
	{
		open_files(argc, argv, &input_file, &output_file);
		pipex(argv, envp);
		// execute(argv, envp);
	}
}
