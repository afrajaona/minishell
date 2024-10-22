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

int	ft_redir_to_tty(char *tty, int fd)
{
	int	tty_fd;

	if (g_sigint == 1)
	{
		tty_fd = open(tty, O_RDONLY);
		if (tty_fd == -1)
		{
			perror("open");
			exit(1);
		}
		if (dup2(tty_fd, fd) == -1)
		{
			perror("dup2");
			close(tty_fd);
			exit(1);
		} 
		close(tty_fd);
	}
	return (0);
}
