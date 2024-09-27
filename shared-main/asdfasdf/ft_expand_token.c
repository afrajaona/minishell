/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:35:48 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:29:58 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void		ft_expand_token(t_data *data, t_token *token)
{
	if ((data == NULL) || (token == NULL))
		return ;
	while (token != NULL)
	{
		token->expand = ft_get_expand(data, token);
		token = token->next;
	}
}
