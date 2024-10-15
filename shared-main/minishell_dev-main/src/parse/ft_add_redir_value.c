/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redir_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:16 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:30 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_add_input_redir(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*token;
	t_redir	*redir;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_INPUT_REDIR) && (token->next != NULL)
		&& (token->next->type == TOKEN_FILE))
	{
		token = token->next;
		redir = ft_new_redir(token, TOKEN_INPUT_REDIR);
		ft_redir_add_back(&cmd->redir, redir);
	}
	token = token->next;
	*token_ptr = token;
}

void	ft_add_output_redir(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*token;
	t_redir	*redir;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_OUTPUT_REDIR) && (token->next != NULL)
		&& (token->next->type == TOKEN_FILE))
	{
		token = token->next;
		redir = ft_new_redir(token, TOKEN_OUTPUT_REDIR);
		ft_redir_add_back(&cmd->redir, redir);
	}
	token = token->next;
	*token_ptr = token;
}

void	ft_add_heredoc_redir(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*token;
	t_redir	*redir;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_HEREDOC) && (token->next != NULL)
		&& (token->next->type == TOKEN_LIMITER))
	{
		token = token->next;
		redir = ft_new_redir(token, TOKEN_HEREDOC);
		ft_redir_add_back(&cmd->redir, redir);
	}
	token = token->next;
	*token_ptr = token;
}

void	ft_add_append_redir(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*token;
	t_redir	*redir;

	if ((cmd == NULL) || (token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	if ((token->type == TOKEN_APPEND) && (token->next != NULL)
		&& (token->next->type == TOKEN_FILE))
	{
		token = token->next;
		redir = ft_new_redir(token, TOKEN_APPEND);
		ft_redir_add_back(&cmd->redir, redir);
	}
	token = token->next;
	*token_ptr = token;
}
