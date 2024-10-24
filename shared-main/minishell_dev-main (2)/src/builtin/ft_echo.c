/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:38:05 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/15 15:48:55 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	char	**args;
	
	if (cmd->arg)
		args = get_cmd_line(cmd->arg->value, cmd->arg->next);
	else
		args = NULL;
	if (!args)
		return (write(1, "\n", 1), 0);
	if (*args)
	{
		if (ft_strlen(*args) == 2 && !ft_strncmp(*args, "-n", 2))
			ft_display_tab(&args[1], 0, 1, 0);
		else
			ft_display_tab(args, 0, 1, 1);
	}
	else
		write(1, "\n", 1);
	ft_clear_tab(args);
	return (0);
}
