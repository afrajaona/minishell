/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:14:36 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/10 15:23:34 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	update_data(t_data *data)
{
	int		fd;
	int		bytes_read;
	char	buffer[100];

	fd = open("temp", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: failed to update exit value\n", 2);
		return ;
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read == -1)
	{
        ft_putstr_fd("minishell: failed to update exit value\n", 2);
        return ;
    }
	data->status = buffer;
	close(fd);
}
