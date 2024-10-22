/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:37:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:29:51 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t			i;
	int				sigle;
	int				res;

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
