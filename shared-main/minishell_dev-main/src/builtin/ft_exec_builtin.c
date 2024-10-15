/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:24:12 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_exec_builtin(t_data *data, t_cmd *cmd, int in_pipe)
{
	int	retval;
	
	if (ft_check_builtin("cd", cmd->value, cmd->arg->value, data))
		retval = cd(data, cmd);
	else if (ft_check_builtin("pwd", cmd->value, cmd->arg->value, data))
		retval = pwd();
	else if (ft_check_builtin("env", cmd->value, cmd->arg->value, data))
		retval = ft_display_tab(data->env, 1, 0, 0);
	else if (ft_check_builtin("echo", cmd->value, cmd->arg->value, data))
		retval = echo(data, cmd);
	else if (ft_check_builtin("exit", cmd->value, cmd->arg->value, data))
		retval = ft_exit(data, cmd);
	else if (ft_check_builtin("unset", cmd->value, cmd->arg->value, data))
		retval = unset(data, cmd);
	else
		retval = ft_export(data, cmd);
	if (in_pipe)
		exit(retval);
	return (retval);
}
