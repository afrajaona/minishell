/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:38:50 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/18 14:42:08 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, t_cmd *cmd)
{
	char	**input;
	int		retval;
	
	if (!cmd->arg)
		return (sort_print(data->ex_var), 0);
	retval = 0;
	input = get_cmd_line(cmd->arg->value, cmd->arg->next);
	if (!input || !*input)
		return (sort_print(data->ex_var), 0);
	while (*input)
	{
		if (handle_export_error(*input))
		{
			retval = 1;
			input++;
		}
		if (ft_strchr(*input, '='))
			ft_insert_var(input, &data->env);
		ft_insert_var(input, &data->ex_var);
		input++;
	}
	ft_clear_tab(input);
	return (retval);
}
