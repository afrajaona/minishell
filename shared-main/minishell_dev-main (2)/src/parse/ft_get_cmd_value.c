/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:54 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_get_cmd_value(t_cmd *cmd, t_token **token_ptr)
{
	t_token		*token;
	t_arg		*arg;
	t_expand	*expand;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_COMMAND) && (token->expand != NULL))
	{
		expand = token->expand;
		if (expand->type == TOKEN_COMMAND)
		{
			cmd->value = ft_strdup(expand->value);
			expand = expand->next;
		}
		while ((expand != NULL)
			&& (expand->type == TOKEN_ARGUMENT))
		{
			arg = ft_new_arg(ft_strdup(expand->value));
			ft_arg_add_back(&cmd->arg, arg);
			expand = expand->next;
		}
	}
	token = token->next;
	*token_ptr = token;
}
