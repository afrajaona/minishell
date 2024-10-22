/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:04 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:45 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

t_expand	*ft_get_expand(t_data *data, t_token *token)
{
	t_expand	*expand;

	if ((data == NULL) || (token == NULL) || (token->value == NULL))
		return (NULL);
	if (token->type == TOKEN_COMMAND)
		expand = ft_get_expand_cmd(data, token->value);
	else if (token->type == TOKEN_ARGUMENT)
		expand = ft_get_expand_arg(data, token->value);
	else if (token->type == TOKEN_LIMITER)
		expand = ft_get_expand_limter(data, token->value);
	else if (token->type == TOKEN_FILE)
		expand = ft_get_expand_file(data, token->value);
	else
		expand = NULL;
	return (expand);
}
