/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:37 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:26 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	ft_check_cmd(t_parse *node)
{
	if ((node == NULL) || (node->type != TOKEN_COMMAND)
		|| (node->data.cmd == NULL))
		return (false);
	else
		return (true);
}

void	ft_init_exec_value(t_exec *exec)
{
	if (exec == NULL)
		return ;
	exec->value = NULL;
	exec->argv = NULL;
}
