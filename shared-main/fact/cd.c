/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:57:23 by arajaona          #+#    #+#             */
/*   Updated: 2024/07/10 14:01:05 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_cmd *cmd, t_data *data)
{
	t_arg	*tmp;
	int		i;
	int		tmp_fd;

	tmp = cmd->arg;
	tmp_fd = dup(1);
	dup2(2, 1);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (i > 1)
	{
		printf("minishell: cd: too many arguments\n");
		dup2(tmp_fd, 1);
		data->status = 1;
		return ;
	}
	if (chdir(cmd->arg->value))
	{
		printf("minishell: cd: %s: %s\n", cmd->arg->value, strerror(errno));
		dup2(tmp_fd, 1);
		data->status = 1;
	}
}
