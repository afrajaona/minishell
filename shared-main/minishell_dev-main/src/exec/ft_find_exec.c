/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:22:06 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:37 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_find_exec(t_data *data, char **filename, t_cmd *cmd)
{
	char	*exec;

	if ((data == NULL) || (filename == NULL)
		|| (cmd == NULL) || (cmd->value == NULL))
		return ;
	if (ft_strchr(cmd->value, '/'))
		exec = ft_strdup(cmd->value);
	else
	{
		exec = ft_find_cmd(cmd->value, data->env);
		if (exec == NULL)
			exit(127);
	}
	if (access(exec, F_OK) == -1)
	{
		free(exec);
		exit(126);
	}
	if (access(exec, X_OK) == -1)
	{
		free(exec);
		exit(127);
	}
	*filename = exec;
}
