/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:30:44 by arajaona          #+#    #+#             */
/*   Updated: 2024/08/12 14:24:04 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_varlen(char *var)
{
	size_t	i;

	i = 0;	
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

static void	delete_var(char	***tab, char *input)
{
	int	i;
	size_t	len;
	
	i = 0;
	while ((*tab)[i] && ft_strncmp((*tab)[i], input, ft_strlen(input)))
		i++;
	if (!(*tab)[i])
		return ;
	len = ft_varlen((*tab)[i]);
	if (len != ft_strlen(input))
		return ;
	free((*tab)[i]);
	while ((*tab)[i])
	{
		(*tab)[i] = (*tab)[i + 1];
		i++;
	}
}

int	unset(t_data *data, t_cmd *cmd)
{
	int	i;
	char	**input;
	
	input = get_cmd_line(cmd->arg->value, cmd->arg->next);
	if (!input || !*input)
		return (0);
	i = 0;
	while (input[i])
	{
		delete_var(&data->env, input[i]);
		delete_var(&data->ex_var, input[i]);
		i++;
	}
	ft_clear_tab(input);
	return (0);
}
