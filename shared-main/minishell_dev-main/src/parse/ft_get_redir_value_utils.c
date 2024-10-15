/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redir_value_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:26:06 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:56 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_list	*ft_get_expand_value(t_expand *expand);

int	ft_get_input_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;
	char	*filename;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_INPUT_REDIR))
		return (-1);
	expand = ft_get_expand_value(token->expand);
	if (expand == NULL)
		return (-1);
	filename = ft_strdup(token->value);
	redir->type = type;
	redir->value.input_redir.n_arg = ft_lstsize(expand);
	redir->value.input_redir.filename = filename;
	redir->value.input_redir.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_output_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;
	char	*filename;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_OUTPUT_REDIR))
		return (-1);
	expand = ft_get_expand_value(token->expand);
	if (expand == NULL)
		return (-1);
	filename = ft_strdup(token->value);
	redir->type = type;
	redir->value.output_redir.n_arg = ft_lstsize(expand);
	redir->value.output_redir.filename = filename;
	redir->value.output_redir.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_append_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;
	char	*filename;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_APPEND))
		return (-1);
	expand = ft_get_expand_value(token->expand);
	if (expand == NULL)
		return (-1);
	filename = ft_strdup(token->value);
	redir->type = type;
	redir->value.append.n_arg = ft_lstsize(expand);
	redir->value.append.filename = filename;
	redir->value.append.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_heredoc_redir(t_redir *redir, t_type type, t_token *token)
{
	char	*limiter;
	char	*expand;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_HEREDOC))
		return (-1);
	limiter = ft_strdup(token->value);
	expand = ft_strdup(token->expand->value);
	redir->type = type;
	redir->value.heredoc.is_exec = false;
	redir->value.heredoc.limiter = limiter;
	redir->value.heredoc.expand = expand;
	redir->next = NULL;
	return (0);
}

static t_list	*ft_get_expand_value(t_expand *expand)
{
	t_list	*values;
	char	*value;

	values = NULL;
	while (expand != NULL)
	{
		value = ft_strdup(expand->value);
		ft_add_content(&values, value);
		expand = expand->next;
	}
	return (values);
}
