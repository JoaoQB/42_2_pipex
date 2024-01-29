/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:18:35 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/29 15:54:30 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_input(int fd)
{
	int		read_char;
	char	*buffer[1];
	// char	*line;

	read_char = read(0, buffer, 1);
	while(read_char > 0)
	{
		// if (!line)
		// 	line = malloc(1);
		write(fd[1], &buffer[0], 1);
		read_char = read(0, buffer, 1);
	}
	// return(line);
}


