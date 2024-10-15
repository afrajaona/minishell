/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:33:11 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/12 13:35:59 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_atoll(const char *nptr)
{
	size_t		i;
	size_t		sigle;
	size_t		res;

	sigle = 1;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] == '\f') || (nptr[i] == '\n')
		|| (nptr[i] == '\r') || (nptr[i] == '\t') || (nptr[i] == '\v'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sigle = -1;
		i++;
	}
	res = 0;
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sigle);
}
