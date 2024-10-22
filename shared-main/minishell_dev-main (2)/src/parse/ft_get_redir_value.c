/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redir_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:26:10 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:00 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_get_redir_value(t_redir *redir, t_type type, t_token *token)
{
	int	res;

	if ((redir == NULL) || (token == NULL))
		return (-1);
	if ((type == TOKEN_INPUT_REDIR) && (token->type == TOKEN_FILE))
		res = ft_get_input_redir(redir, TOKEN_INPUT_REDIR, token);
	else if ((type == TOKEN_OUTPUT_REDIR) && (token->type == TOKEN_FILE))
		res = ft_get_output_redir(redir, TOKEN_OUTPUT_REDIR, token);
	else if ((type == TOKEN_HEREDOC) && (token->type == TOKEN_LIMITER))
		res = ft_get_heredoc_redir(redir, TOKEN_HEREDOC, token);
	else if ((type == TOKEN_APPEND) && (token->type == TOKEN_FILE))
		res = ft_get_append_redir(redir, TOKEN_APPEND, token);
	else
		return (-1);
	return (res);
}
