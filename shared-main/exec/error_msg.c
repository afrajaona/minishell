/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:57:02 by arajaona          #+#    #+#             */
/*   Updated: 2024/09/26 16:59:26 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error_msg(char *target, char *message, int path_on)
{
	int	tmp_fd;

	tmp_fd = dup(1);
	dup2(2, 1);
	if (path_on)
		printf("%s: %s\n", target, message);
	else
		printf("minishell: %s: %s\n", target, message);
	dup2(tmp_fd, 1);
	exit(EXIT_FAILURE);
}
