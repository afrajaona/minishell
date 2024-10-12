/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:01:22 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:29:21 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_init(t_data *data, int status, char **env)
{
	data->env = ft_tab_dup(env);
	data->export_env = ft_tab_dup(env);
	data->status = status;
}

void	ft_free_data(t_data *data)
{
	free_tab(data->env);
	free_tab(data->export_env);
	data->env = NULL;
	data->export_env = NULL;
}
