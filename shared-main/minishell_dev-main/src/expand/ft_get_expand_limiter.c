/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_expand_limiter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:24:09 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:40 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

t_expand	*ft_get_expand_limter(t_data *data, char *limiter)
{
	char		*trim;

	(void) data;
	trim = NULL;
	ft_trim_quotes(&trim, limiter);
	return (ft_new_expand(TOKEN_LIMITER, trim));
}
