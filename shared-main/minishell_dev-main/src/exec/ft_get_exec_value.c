/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_exec_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:22:12 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_get_argv(t_data *data, char ***argv_ptr, t_cmd *cmd);

void	ft_get_exec_value(t_data *data, t_exec *exec, t_cmd *cmd)
{
	if ((data == NULL) || (exec == NULL) || (cmd == NULL))
		return ;
	ft_find_exec(data, &exec->value, cmd);
	ft_get_argv(data, &exec->argv, cmd);
}

static void	ft_get_argv(t_data *data, char ***argv_ptr, t_cmd *cmd)
{
	t_arg	*arg;
	t_list	*temp;

	(void) data;
	temp = NULL;
	if ((data == NULL) || (argv_ptr == NULL)
		|| (cmd == NULL) || (cmd->value == NULL))
		return ;
	ft_add_content(&temp, cmd->value);
	arg = cmd->arg;
	while (arg != NULL)
	{
		ft_add_content(&temp, arg->value);
		arg = arg->next;
	}
	*argv_ptr = ft_to_tab(temp);
}
