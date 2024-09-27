/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:38:49 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:31:05 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	ft_set_type(t_type *type, char *lexeme, t_flag *flag);
static void	ft_set_operator_type(t_type *type, int value, t_flag *flag);
static void	ft_set_general_type(t_type *type, t_flag *flag);

int	ft_get_token(t_data *data, t_token **token, char *line)
{
	t_list		*lexeme;
	t_token		*p_tail;

	if ((data == NULL) || (token == NULL) || (line == NULL))
		return (-1);
	ft_token_init(token, &p_tail);
	ft_get_lexeme(&lexeme, line);
	ft_tokenize(token, &p_tail, lexeme);
	ft_expand_token(data, *token);
	ft_clear_lexeme(&lexeme);
	return (0);
}

int	ft_tokenize(t_token **head_ptr, t_token **tail_ptr, t_list *lexeme)
{
	t_type	type;
	char	*value;
	t_token	*token;
	t_flag	flag;

	if ((head_ptr == NULL) || (tail_ptr == NULL) || (lexeme == NULL))
		return (-1);
	ft_flag_init(&flag);
	while (lexeme != NULL)
	{
		value = (char *) lexeme->content;
		ft_set_type(&type, value, &flag);
		token = ft_new_token(type, value);
		ft_add_token(head_ptr, tail_ptr, token);
		lexeme = lexeme->next;
	}
	return (0);
}

static void	ft_set_type(t_type *type, char *lexeme, t_flag *flag)
{
	if (ft_s_compare(lexeme, LEXEME_HEREDOC))
		ft_set_operator_type(type, TOKEN_HEREDOC, flag);
	else if (ft_s_compare(lexeme, LEXEME_INPUT_REDIR))
		ft_set_operator_type(type, TOKEN_INPUT_REDIR, flag);
	else if (ft_s_compare(lexeme, LEXEME_APPEND))
		ft_set_operator_type(type, TOKEN_APPEND, flag);
	else if (ft_s_compare(lexeme, LEXEME_OUTPUT_REDIR))
		ft_set_operator_type(type, TOKEN_OUTPUT_REDIR, flag);
	else if (ft_s_compare(lexeme, LEXEME_PIPE))
		ft_set_operator_type(type, TOKEN_PIPE, flag);
	else
		ft_set_general_type(type, flag);
}

static void	ft_set_operator_type(t_type *type, int value, t_flag *flag)
{
	*type = value;
	if (value == TOKEN_HEREDOC)
		ft_set_flag(flag, false, flag->cmd, true);
	else if (value == TOKEN_INPUT_REDIR)
		ft_set_flag(flag, true, flag->cmd, false);
	else if (value == TOKEN_APPEND)
		ft_set_flag(flag, true, flag->cmd, flag->heredoc);
	else if (value == TOKEN_OUTPUT_REDIR)
		ft_set_flag(flag, true, flag->cmd, flag->heredoc);
	else
		ft_set_flag(flag, false, false, false);
}

static void	ft_set_general_type(t_type *type, t_flag *flag)
{
	if ((flag->cmd == true) && (flag->redir == false)
		&& (flag->heredoc == false))
	{
		*type = TOKEN_ARGUMENT;
		ft_set_flag(flag, flag->redir, flag->cmd, flag->heredoc);
	}
	if ((flag->cmd == false) && (flag->redir == false)
		&& (flag->heredoc == false))
	{
		*type = TOKEN_COMMAND;
		ft_set_flag(flag, flag->redir, true, flag->heredoc);
	}
	if ((flag->redir == true) && (flag->heredoc == false))
	{
		*type = TOKEN_FILE;
		ft_set_flag(flag, false, flag->cmd, flag->heredoc);
	}
	if ((flag->heredoc == true) && (flag->redir == false))
	{
		*type = TOKEN_LIMITER;
		ft_set_flag(flag, flag->redir, flag->cmd, false);
	}
}
