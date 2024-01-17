/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:04:11 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/16 13:32:47 by jqueijo-         ###   ########.fr       */
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
