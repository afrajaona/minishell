/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:20:31 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:02:36 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ft_print_expand(t_expand *expand)
{
	if (expand == NULL)
		ft_printf("token expand: NULL\n");
	while (expand != NULL)
	{
		ft_printf("token expand: [%s] : ", expand->value);
		ft_print_type(expand->type);
		expand = expand->next;
	}
}
