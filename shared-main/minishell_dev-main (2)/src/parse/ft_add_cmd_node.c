/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:24:50 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:15 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_add_cmd_value(t_cmd *cmd, t_token **token_ptr);
static void	ft_get_next_token(t_token **token_ptr);

void	ft_add_cmd_node(t_parse **parse_ptr, t_token **token_ptr)
{
	t_parse	*node;
	int		res;

	node = ft_new_node(TOKEN_COMMAND);
	if (node == NULL)
	{
		ft_next_token(token_ptr, TOKEN_COMMAND);
		return ;
	}
	node->data.cmd = ft_new_cmd();
	if (node->data.cmd == NULL)
	{
		free(node);
		ft_next_token(token_ptr, TOKEN_COMMAND);
		return ;
	}
	res = ft_add_cmd_value(node->data.cmd, token_ptr);
	if (res == -1)
	{
		free(node);
		ft_next_token(token_ptr, TOKEN_COMMAND);
		return ;
	}
	ft_add_parse(parse_ptr, node);
}

static int	ft_add_cmd_value(t_cmd *cmd, t_token **token_ptr)
{
	t_token		*token;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return (-1);
	token = *token_ptr;
	while ((token != NULL) && (token->type != TOKEN_PIPE))
	{
		if (token->type == TOKEN_COMMAND)
			ft_get_cmd_value(cmd, &token);
		else if (token->type == TOKEN_ARGUMENT)
			ft_get_arg_value(cmd, &token);
		else if (token->type == TOKEN_INPUT_REDIR)
			ft_add_input_redir(cmd, &token);
		else if (token->type == TOKEN_HEREDOC)
			ft_add_heredoc_redir(cmd, &token);
		else if (token->type == TOKEN_OUTPUT_REDIR)
			ft_add_output_redir(cmd, &token);
		else if (token->type == TOKEN_APPEND)
			ft_add_append_redir(cmd, &token);
		else
			ft_get_next_token(&token);
		*token_ptr = token;
	}
	return (0);
}

static void	ft_get_next_token(t_token **token_ptr)
{
	t_token	*token;

	if ((token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	token = token->next;
	*token_ptr = token;
}
