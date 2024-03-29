/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:20:13 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/05 14:34:15 by jqueijo-         ###   ########.fr       */
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

void	open_file(int argc, char **argv, int *fd, int file_nbr);
void	ft_error(char *string);
void	ft_free_doublearray(char **argv);
void	pipex(char *argv, char **envp);
int		ft_strcmp(const char *str, const char *str2);
void	parent_process(int *pipe_end);
void	child_process(int *pipe_end, char *argv, char **envp);
void	execute(char *argv, char **envp);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**get_paths(char **envp);
char	*check_paths(char **possible_paths, char *command);

#endif
