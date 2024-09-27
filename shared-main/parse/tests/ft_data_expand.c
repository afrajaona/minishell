/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:01:22 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:32:48 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data, int exit_status, char **env)
{
	data->env = env;
	data->exit = ft_itoa(exit_status);
}

void	ft_free_data(t_data *data)
{
	free(data->exit);
}
