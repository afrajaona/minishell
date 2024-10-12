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

size_t	ft_varlen(char *var)
{
	size_t	i;

	i = 0;	
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void	delete_var(char	***tab, char *input)
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

void	unset(char ***env_var, char ***export_var, char **input)
{
	int	i;
	
	i = 0;
	if (!*input)
		return ;
	while (input[i])
	{
		delete_var(env_var, input[i]);
		delete_var(export_var, input[i]);
		i++;
	}
	free_tab(input);
}
