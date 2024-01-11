/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:20:13 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/11 18:17:16 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> // System calls
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function
# include <errno.h> // Error handling
# include <sys/wait.h> // Wait and waitpid function
# include <fcntl.h> // Open function

void	open_files(int argc, char **argv, int *fd_in, int *fd_out);
void	ft_error(char *string);
void	pipex(int *fd_in, int *fd_out, char **argv, char **envp);

#endif
