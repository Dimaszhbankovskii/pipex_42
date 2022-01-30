/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladarys <ladarys@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:22:03 by ladarys           #+#    #+#             */
/*   Updated: 2022/01/21 14:23:39 by ladarys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_buffer(int read_bytes, char *buffer)
{
	free(buffer);
	buffer = NULL;
	if (read_bytes < 0)
		return (-1);
	else if (read_bytes == 0)
		return (0);
	else
		return (1);
}
