/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:22:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wait_cmds(t_data *data, t_parse *parse)
{
	pid_t	wpid;
	int		wait_status;

	wait_status = 0;
	wpid = 0;
	while (parse != NULL)
	{
		if ((parse->type != TOKEN_COMMAND) || (parse->data.cmd == NULL)
			|| (parse->data.cmd->pid == -1))
			parse = parse->next;
		else
		{
			wpid = waitpid(parse->data.cmd->pid, &wait_status, 0);
			if (wpid == -1)
				data->exit.value = 1;
			if (WIFEXITED(wait_status))
				data->exit.value = WEXITSTATUS(wait_status);
			if (WIFSIGNALED(wait_status))
			{
				if (WTERMSIG(wait_status) == 3)
					ft_printf("Quit (core dumped)\n");
				else if (WTERMSIG(wait_status) == 2)
					ft_printf("\n");
			}
			parse = parse->next;
		}
	}
}
