/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:11:14 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/22 11:30:50 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

typedef enum e_token_type	t_token_type;
typedef enum e_expand_type	t_expand_type;
typedef struct s_token		t_token;
typedef struct s_expand		t_expand;

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# define LEXEME_PIPE "|"
# define LEXEME_I_REDIR "<"
# define LEXEME_O_REDIR ">"
# define LEXEME_HEREDOC "<<"
# define LEXEME_APPEND ">>"

struct s_token
{
	t_token_type	type;
	char			*value;
	t_list			*expand;
	t_token			*next;
	t_token			*prev;
};

t_list	*ft_get_lexeme(char *s);
void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index);
t_token	*ft_new_token(t_token_type type, char *value, t_list *expand);
void	ft_print_token(t_token *token);

static t_bool	ft_is_separator(char *s, size_t i);
static void		ft_add_lexeme(t_list **lexeme, char *s, size_t *index);
static void		ft_add_operator(t_list **lexeme, char *s, size_t *index);

t_bool	ft_s_compare(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (true);
	else
		return (false);
}

void	ft_add_content(t_list **lst, void *content)
{
	ft_lstadd_back(lst, ft_lstnew(content));
}

static t_bool	ft_is_separator(char *s, size_t i);
static void		ft_add_lexeme(t_list **lexeme, char *s, size_t *index);
static void		ft_add_operator(t_list **lexeme, char *s, size_t *index);

t_list	*ft_get_lexeme(char *s)
{
	size_t	i;
	t_list	*lexeme;

	i = 0;
	lexeme = NULL;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) && (s[i] != '\0'))
			i++;
		ft_add_lexeme(&lexeme, s, &i);
		ft_add_operator(&lexeme, s, &i);
	}
	return (lexeme);
}

static t_bool	ft_is_separator(char *s, size_t i)
{
	if (ft_isspace(s[i])
		|| ft_s_compare(&s[i], LEXEME_I_REDIR)
		|| ft_s_compare(&s[i], LEXEME_O_REDIR)
		|| ft_s_compare(&s[i], LEXEME_PIPE)
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
		if ((s[i] == SINGLE_QUOTE) || (s[i] == DOUBLE_QUOTE))
			ft_add_str_in_delim(&temp, s, s[i], &i);
		i++;
		if ((s[i] == '\0') || ft_is_separator(s, i))
		{
			ft_add_content(lexeme, ft_lst_to_tab(temp));
			temp = NULL;
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
	else if (ft_s_compare(&s[i], LEXEME_I_REDIR))
		operator = ft_strdup(LEXEME_I_REDIR);
	else if (ft_s_compare(&s[i], LEXEME_APPEND))
		operator = ft_strdup(LEXEME_APPEND);
	else if (ft_s_compare(&s[i], LEXEME_O_REDIR))
		operator = ft_strdup(LEXEME_O_REDIR);
	else
		operator = NULL;
	if (operator != NULL)
	{
		ft_add_content(lexeme, operator);
		i += ft_strlen(operator);
	}
	*index = i;
}

void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index)
{
	size_t	i;

	i = *index + 1;
	while ((s[i] != '\0') && (s[i] != delim))
	{
		ft_lstadd_back(temp, ft_lstnew(&s[i]));
		i++;
	}
	ft_lstadd_back(temp, ft_lstnew(&s[i]));
	*index = i;
}
//-----------------------------------------------------------------------------------------
void	ft_add_token(t_token **head_ptr, t_token **tail_ptr, t_token *token)
{
	t_token	*tail;

	if (token == NULL)
		return ;
	tail = *tail_ptr;
	if (*head_ptr == NULL)
	{
		*head_ptr = token;
		*tail_ptr = token;
	}
	else
	{
		token->prev = tail;
		tail->next = token;
		*tail_ptr = token;
	}
}

void	ft_tokenize(t_data *data, t_token **head_ptr, t_token **tail_ptr, t_list *lexeme)
{
	t_token_type	type;
	char			*value;
	t_list		*expand;

	t_bool			in_cmd;
	t_bool			redir;
	t_bool			heredoc;

	in_cmd = false;
	redir = false;
	heredoc = false;
	(void) data;
	expand = NULL;
	while (lexeme != NULL)
	{
		value = (char *) lexeme->content;
		if (ft_strncmp(value, "|", ft_strlen("|")) == 0)
		{
			type = TOKEN_PIPE;
			in_cmd = false;
			redir = false;
			heredoc = false;
		}
		else if (ft_strncmp(value, "<<", ft_strlen("<<")) == 0)
		{
			type = TOKEN_HEREDOC;
			heredoc = true;
			redir = false;
		}
		else if (ft_strncmp(value, ">>", ft_strlen(">>")) == 0)
		{
			type = TOKEN_APPEND;
			redir = true;
		}
		else if (ft_strncmp(value, "<", ft_strlen("<")) == 0)
		{
			type = TOKEN_INPUT_REDIR;
			redir = true;
			heredoc = false;
		}
		else if (ft_strncmp(value, ">", ft_strlen(">")) == 0)
		{
			type = TOKEN_OUTPUT_REDIR;
			redir = true;
		}
		else
		{
			if ((in_cmd == true) && (redir == false) && (heredoc == false))
			{
				type = TOKEN_ARGUMENT;
				expand = ft_expand_token(data, type, value);
			}
			if ((in_cmd == false) && (redir == false) && (heredoc == false))
			{
				type = TOKEN_COMMAND;
				in_cmd = true;
				expand = ft_expand_token(data, type, value);
			}
			if ((redir == true) && (heredoc == false))
			{
				type = TOKEN_FILE;
				redir = false;
				expand = ft_expand_token(data, type, value);
			}
			if ((heredoc == true) && (redir == false))
			{
				type = TOKEN_LIMITER;
				heredoc = false;
				expand = ft_expand_token(data, type, value);
			}
		}
		//ft_printf("type: %d  in_cmd: %d  redir: %d  heredoc: %d\n", type, in_cmd, redir, heredoc);
		ft_add_token(head_ptr, tail_ptr, ft_new_token(type, value, expand));
		expand = NULL;
		lexeme = lexeme->next;
	}
	ft_printf("\n");
}

void	ft_initialize_tokens(t_token **head_ptr, t_token **tail_ptr)
{
	*head_ptr = NULL;
	*tail_ptr = NULL;
}
//-----------------------------------------------------------------------------------------
void	ft_check_token(t_token *token)
{
	if (token == NULL)
		return ;
	if ((token->type == TOKEN_PIPE) && (token->prev == NULL))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", token->value);
		exit(1);
	}
	while (token != NULL)
	{
		if (((token->type == TOKEN_INPUT_REDIR) || (token->type == TOKEN_OUTPUT_REDIR) || (token->type == TOKEN_APPEND))
			&& ((token->next == NULL) || (token->next->type != TOKEN_FILE)))
		{
			if (token->next == NULL)
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
			else
				ft_printf("minishell: syntax error near unexpected token `%s'\n", token->next->value);
			exit(1);
		}
		if ((token->type == TOKEN_HEREDOC) && ((token->next == NULL) || (token->next->type != TOKEN_LIMITER)))
		{
			if (token->next == NULL)
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
			else
				ft_printf("minishell: syntax error near unexpected token `%s'\n", token->next->value);
			exit(1);
				
		}
		if ((token->type == TOKEN_PIPE) && (token->next != NULL) && (token->next->type == TOKEN_PIPE))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", token->value);
			exit(1);
		}
		token = token->next;
	}
}

t_token	*ft_parse_cmd(t_data *data, char *line)
{
	t_token	*head;
	t_token	*tail;
	t_list	*lexeme;

	ft_initialize_tokens(&head, &tail);
	lexeme = ft_get_lexeme(line);
	ft_tokenize(data, &head, &tail, lexeme);
	ft_check_token(head);
	return (head);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		exit_status;
	char	*line;
	t_token	*tokens;

	(void) argc;
	(void) argv;
	exit_status = 0;
	ft_init_data(&data, exit_status, env);
	line = readline(PROMPT);
	while (line != NULL)
	{
		if (ft_isempty(line) == false)
		{
			add_history(line);
			tokens = ft_parse_cmd(&data, line);
			ft_print_token(tokens);
		}
		line = readline(PROMPT);
	}
	rl_clear_history();
	return (0);
}

t_token	*ft_new_token(t_token_type type, char *value, t_list *expand)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->value = value;
	new->expand = expand;
	new->prev = NULL;
	new->next = NULL;
	return (new);
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
		ft_printf("Expand:\n");
		ft_print_lst(token->expand);
		ft_printf("\n");
		token = token->next;
	}
}
