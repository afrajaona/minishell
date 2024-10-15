/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_to_tty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:08:20 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/15 02:20:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_redir_to_tty(t_data *data)
{
	int	fd;

	if (g_sigint == 1)
	{
		fd = open(data->tty, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		} 
		close(fd);
		g_sigint = 0;
	}
	return (0);
}