/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:17 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_execve_cmd(t_data *data, t_cmd *cmd);

void	ft_exec_cmd(t_data *data, t_parse *parse)
{
	t_cmd	*cmd;

	if ((data == NULL) || (ft_check_cmd(parse) == false))
		return ;
	cmd = parse->data.cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
		data->exit.value = 1;
	if (cmd->pid == 0)
	{
		ft_execve_cmd(data, cmd);
		exit(42);
	}
}

static void	ft_execve_cmd(t_data *data, t_cmd *cmd)
{
	t_exec	exec;

	if ((data == NULL) || (cmd == NULL) || (cmd->value == NULL))
		return ;
	ft_init_exec_value(&exec);
	ft_get_exec_value(data, &exec, cmd);
	ft_set_default_signal();
	execve(exec.value, exec.argv, data->env);
	if (errno == EACCES)
		exit(1);
	else
		exit(1);
}
