/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:18:35 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/29 16:25:44 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_input(int *fd)
{
	int		read_char;
	char	*buffer[1];
	// char	*line;

	read_char = read(0, buffer, 1);
	while(read_char > 0)
	{
		// if (!line)
		// 	line = malloc(1);
		write(fd, buffer, read_char);
		read_char = read(0, buffer, 1);
	}
	// return(line);
}

void	get_doc(int *fd)
{
	read_input(fd);

}


