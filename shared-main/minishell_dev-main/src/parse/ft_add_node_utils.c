/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:24:57 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:19 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->pid = -1;
	cmd->value = NULL;
	cmd->redir = NULL;
	cmd->arg = NULL;
	return (cmd);
}

t_pipe	*ft_new_pipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) malloc(sizeof(t_pipe));
	if (pipe == NULL)
		return (NULL);
	return (pipe);
}

void	ft_next_token(t_token **token_ptr, t_type type)
{
	t_token	*token;

	if ((token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token != NULL) && (type == TOKEN_COMMAND))
	{
		while ((token != NULL) && (token->type != TOKEN_PIPE))
			token = token->next;
	}
	if ((token != NULL) && (type == TOKEN_PIPE))
		token = token->next;
	*token_ptr = token;
}
