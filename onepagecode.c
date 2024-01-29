/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onepagecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:42:49 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/29 12:44:31 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *str, const char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return (str[i] - str2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && size && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size - i != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len + 2));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = '/';
	j = -1;
	while (s2[++j])
		dest[i++] = s2[j];
	*(dest + i) = '\0';
	return (dest);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len == 0 && !big)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

/* Ft_split */
static int	substr_count(char const *s, int c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*fill_substr(const char *src, size_t len)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len);
	return (dest);
}

static char	**ft_free(char **strs, int count)
{
	while (--count >= 0)
		free(*(strs + count));
	free(strs);
	return (NULL);
}

static int	iterate_i(const char *s, int i, char c)
{
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		i;
	int		j;
	int		i_word;

	split_strs = (char **)malloc((substr_count(s, c) + 1) * sizeof(char *));
	if (!split_strs || !s)
		return (NULL);
	j = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			i++;
		i_word = i;
		i = iterate_i(s, i, c);
		if (i_word < i)
		{
			*(split_strs + j++) = fill_substr(&s[i_word], (i - i_word) + 1);
			if (!(*(split_strs + j - 1)))
				return (ft_free(split_strs, j));
		}
	}
	*(split_strs + j) = NULL;
	return (split_strs);
}

/* Continues */
void	ft_error(char *string)
{
	perror(string);
	// exit(EXIT_FAILURE);
}

void	ft_free_doublearray(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**get_paths(char **envp)
{
	char	**command_paths;
	char	*paths;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	paths = *envp;
	while (*paths != '/')
		paths++;
	command_paths = ft_split(paths, ':');
	return (command_paths);
}

char	*check_paths(char **possible_paths, char *command)
{
	char	*cmd_path;
	int		fd;

	while(*possible_paths)
	{
		cmd_path = ft_strjoin(*possible_paths, command);
		fd = access(cmd_path, F_OK);
		if (fd == 0)
			return(cmd_path);
		possible_paths++;
		free(cmd_path);
	}
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**command;
	char	**possible_paths;
	char	*command_path;

	command = ft_split(argv, ' ');
	possible_paths = get_paths(envp);
	if (!command)
		ft_error("");
	command_path = check_paths(possible_paths, *command);
	if (!command_path)
		ft_error("command not found");
	else
		execve(command_path, command, envp);
	write(2, "reached cleaning child\n", 24);
	free(command_path);
	ft_free_doublearray(command);
	ft_free_doublearray(possible_paths);
	write(2, "finished cleaning\n", 19);
}

void	open_files(int argc, char **argv, int *fd_in, int *fd_out)
{
	if (ft_strcmp(argv[1], "here_doc") != 0)
	{
		*fd_in = open(argv[1], O_RDONLY);
		*fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (*fd_in == -1 || *fd_out == -1)
			ft_error("Error in open_files\n");
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
			ft_error("Error in open_files\n");
		//dup2() terminal -> stdin_fileno;
	}
}

void	child_process(int *pipe_end, char *argv, char **envp)
{
	write(2, "reached child\n", 14);
	close(pipe_end[0]);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	execute(argv, envp);
}

void	parent_process(int *pipe_end, char *argv, char **envp)
{
	write(2, "reached parent\n", 15);
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
		ft_error("Pipe error\n");
	process_id = fork();
	if (process_id < 0)
		ft_error("Fork error\n");
	if (process_id == 0)
		child_process(pipe_end, argv, envp);
	else
		parent_process(pipe_end, argv, envp);
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
