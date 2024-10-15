/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:20:49 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:02:51 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ft_print_token(t_token *token)
{
	while (token != NULL)
	{
		ft_printf("\ntoken value : [%s] : ", token->value);
		ft_print_type(token->type);
		ft_print_expand(token->expand);
		token = token->next;
	}
}
