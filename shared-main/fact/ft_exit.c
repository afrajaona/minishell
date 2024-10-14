/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:25:13 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/12 14:36:40 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_cmd *cmd)
{
	int		i;
	t_arg 	*tmp;

	i = 0;
	tmp = cmd->arg;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		invalid_arg(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		sign = 1;
		i++;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	if (sign == 0 && i > 18)
		return (1);
	if (sign == 1 && i > 19)
		return (1); 
	return (0);
}

void	exit_syntax_error(char *s)
{
	int	tmp;

	tmp = dup(1);
	dup2(2, 1);
	printf("minishell: exit: %s: numeric argument required\n", s);
	dup2(tmp, 1);
	exit(2);
}

// needs to cleanup all data strutures

void	ft_exit(t_data *data, t_cmd *cmd)
{
	size_t	exit_val;
	int		arg_count;

	arg_count = count_args(cmd);
	if (!arg_count)
		exit(data->status);
	if (arg_count > 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit(1);
	}
	if (invalid_arg(cmd->arg->value))
		exit_syntax_error(cmd->arg->value);
	exit_val = ft_atoll(cmd->arg->value) % 256;
	exit(exit_val);
}
