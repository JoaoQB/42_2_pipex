/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:20:13 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/18 18:28:40 by jqueijo-         ###   ########.fr       */
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
void	pipex(char *argv, char **envp);
int		ft_strcmp(const char *str, const char *str2);
void	parent_process(int *pipe_end, char *argv, char **envp);
void	child_process(int *pipe_end, char *argv, char **envp);
void	execute(char *argv, char **envp);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);

#endif
