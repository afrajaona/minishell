/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:29:16 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:30:38 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_bool	ft_is_separator(char *s, size_t i);
static void		ft_add_lexeme(t_list **lexeme, char *s, size_t *index);
static void		ft_add_operator(t_list **lexeme, char *s, size_t *index);

int	ft_get_lexeme(t_list **lexeme_ptr, char *s)
{
	size_t	i;
	t_list	*lexeme;

	if ((lexeme_ptr == NULL) || (s == NULL))
		return (-1);
	i = 0;
	lexeme = NULL;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) && (s[i] != '\0'))
			i++;
		ft_add_lexeme(&lexeme, s, &i);
		ft_add_operator(&lexeme, s, &i);
	}
	*lexeme_ptr = lexeme;
	return (0);
}

static t_bool	ft_is_separator(char *s, size_t i)
{
	if (ft_isspace(s[i])
		|| ft_s_compare(&s[i], LEXEME_PIPE)
		|| ft_s_compare(&s[i], LEXEME_INPUT_REDIR)
		|| ft_s_compare(&s[i], LEXEME_OUTPUT_REDIR)
		|| ft_s_compare(&s[i], LEXEME_HEREDOC)
		|| ft_s_compare(&s[i], LEXEME_APPEND))
		return (true);
	else
		return (false);
}

static void	ft_add_lexeme(t_list **lexeme, char *s, size_t *index)
{
	size_t	i;
	t_list	*temp;

	temp = NULL;
	if ((lexeme == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index;
	while ((s[i] != '\0') && (ft_is_separator(s, i) == false))
	{
		ft_add_content(&temp, &s[i]);
		if (((s[i] == SINGLE_QUOTE) || (s[i] == DOUBLE_QUOTE))
			&& ft_quotes_isclose(s, s[i], i))
			ft_add_str_in_delim(&temp, s, s[i], &i);
		if (s[i] != '\0')
			i++;
		if ((s[i] == '\0') || ft_is_separator(s, i))
		{
			ft_add_content(lexeme, ft_lst_to_tab(temp));
			ft_clear_tmp(&temp);
		}
	}
	*index = i;
}

static void	ft_add_operator(t_list **lexeme, char *s, size_t *index)
{
	size_t	i;
	char	*operator;

	if ((lexeme == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index;
	if (ft_s_compare(&s[i], LEXEME_PIPE))
		operator = ft_strdup(LEXEME_PIPE);
	else if (ft_s_compare(&s[i], LEXEME_HEREDOC))
		operator = ft_strdup(LEXEME_HEREDOC);
	else if (ft_s_compare(&s[i], LEXEME_INPUT_REDIR))
		operator = ft_strdup(LEXEME_INPUT_REDIR);
	else if (ft_s_compare(&s[i], LEXEME_APPEND))
		operator = ft_strdup(LEXEME_APPEND);
	else if (ft_s_compare(&s[i], LEXEME_OUTPUT_REDIR))
		operator = ft_strdup(LEXEME_OUTPUT_REDIR);
	else
		operator = NULL;
	if (operator != NULL)
	{
		ft_add_content(lexeme, operator);
		i += ft_strlen(operator);
	}
	*index = i;
}
