/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:14:36 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/10 15:23:34 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	update_data(t_data *data)
{
	if (g_received_sigint)
		data->status = g_received_sigint;
	g_received_sigint = 0;
}
