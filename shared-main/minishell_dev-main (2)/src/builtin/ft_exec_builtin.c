/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:24:12 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/24 13:30:35 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_exec_builtin(t_data *data, t_cmd *cmd, int no_pipe)
{
	int		retval;
	char	*arg_value;

	if (cmd->arg)
		arg_value = cmd->arg->value;
	else
		arg_value = NULL;
	if (ft_check_builtin("cd", cmd->value))
		retval = cd(data, cmd);
	else if (ft_check_builtin("pwd", cmd->value))
		retval = pwd();
	else if (ft_check_builtin("env", cmd->value))
		retval = ft_display_tab(data->env, 1, 0, 0);
	else if (ft_check_builtin("echo", cmd->value))
		retval = ft_echo(cmd);
	else if (ft_check_builtin("exit", cmd->value))
		retval = ft_exit(data, cmd, no_pipe);
	else if (ft_check_builtin("unset", cmd->value))
		retval = unset(data, cmd);
	else
		retval = ft_export(data, cmd);
	return (retval);
}
