/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:47 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_get_arg_value(t_cmd *cmd, t_token **token_ptr)
{
	t_token		*token;
	t_arg		*arg;
	t_expand	*expand;
	char		*value;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_ARGUMENT) && (token->expand != NULL))
	{
		expand = token->expand;
		while ((expand != NULL)
			&& (expand->type == TOKEN_ARGUMENT))
		{
			value = ft_strdup(expand->value);
			arg = ft_new_arg(value);
			ft_arg_add_back(&cmd->arg, arg);
			expand = expand->next;
		}
	}
	token = token->next;
	*token_ptr = token;
}
