/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/08 11:17:12 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

# define PROMPT "tests> "

void	ft_print_lst(t_list *lst)
{
	char	*s;

	while (lst != NULL)
	{
		s = (char *) lst->content;
		ft_printf("[%s]\n", s);
		lst = lst->next;
	}
}

char	*ft_readline(const char *prompt)
{
	size_t	i;
	char	*line;
	t_list	*temp;
	char	*s;

	ft_printf(prompt);
	s = get_next_line(0);
	if (s == NULL)
		return (NULL);
	temp = NULL;
	i = 0;
	while ((s[i] != '\n') && (s[i] != '\0'))
	{
		ft_lstadd_back(&temp, ft_lstnew(&s[i]));
		i++;
	}
	line = ft_to_str(temp);
	free(s);
	ft_clear_tmp(&temp);
	return (line);
}

void	ft_print_type(int type)
{
	if (type == TOKEN_PIPE)
		ft_printf("TOKEN_PIPE\n");
	else if (type == TOKEN_HEREDOC)
		ft_printf("TOKEN_HEREDOC\n");
	else if (type == TOKEN_APPEND)
		ft_printf("TOKEN_APPEND\n");
	else if (type == TOKEN_INPUT_REDIR)
		ft_printf("TOKEN_INPUT_REDIR\n");
	else if (type == TOKEN_OUTPUT_REDIR)
		ft_printf("TOKEN_OUTPUT_REDIR\n");
	else if (type == TOKEN_ARGUMENT)
		ft_printf("TOKEN_ARGUMENT\n");
	else if (type == TOKEN_FILE)
		ft_printf("TOKEN_FILE\n");
	else if (type == TOKEN_LIMITER)
		ft_printf("TOKEN_LIMITER\n");
	else
		ft_printf("TOKEN_COMMAND\n");
}

void	ft_print_token(t_token *token)
{
	while (token != NULL)
	{
		ft_printf("[%s]: ", token->value);
		ft_print_type(token->type);
		token = token->next;
	}
}

int	main(void)
{
	char	*line;
	t_list	*lexeme;
	t_token	*token;
	t_token	*p_tail;

	ft_token_init(&token, &p_tail);
	line = ft_readline(PROMPT);
	while (line != NULL)
	{
		if (ft_isempty(line))
			free(line);
		else
		{
			ft_get_lexeme(&lexeme, line);
			ft_tokenize(&token, &p_tail, lexeme);
			ft_print_token(token);
			ft_clear_lexeme(&lexeme);
			ft_clear_token(&token);
			free(line);
		}
		line = ft_readline(PROMPT);
	}
	return (0);
}
