/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:01:22 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:32:48 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_data_init(t_data *data, int status, char **env)
{
	data->env = env;
	data->status = ft_itoa(status);
}

void	ft_free_data(t_data *data)
{
	free(data->status);
	data->status = NULL;
}
