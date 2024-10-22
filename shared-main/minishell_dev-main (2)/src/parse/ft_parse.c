/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:15:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:11 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_bool	ft_last_ispipe(t_parse *parse);
static void	ft_get_unclose_pipe(t_data *data, t_parse **parse_ptr, t_list **history);

int	ft_check_token(t_data *data, t_token *token)
{
	if ((data == NULL) || (token == NULL))
		return (1);
	if ((token->type == TOKEN_PIPE) && (token->prev == NULL))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", token->value);
		data->exit.value = 2;
		return (1);
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
			data->exit.value = 2;
			return (1);
		}
		if ((token->type == TOKEN_HEREDOC) && ((token->next == NULL) || (token->next->type != TOKEN_LIMITER)))
		{
			if (token->next == NULL)
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
			else
				ft_printf("minishell: syntax error near unexpected token `%s'\n", token->next->value);
			data->exit.value = 2;
			return (1);		
		}
		if ((token->type == TOKEN_PIPE) && (token->next != NULL) && (token->next->type == TOKEN_PIPE))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", token->value);
			data->exit.value = 2;
			return (1);
		}
		token = token->next;
	}
	return (0);
}

void	ft_create_pipe(t_data *data, int *pipefd)
{
	if ((data == NULL) || (pipefd == NULL))
		return ;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

t_bool	ft_quote_in_str(char *s)
{
	size_t	i;

	if (s == NULL)
		return (false);
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == SINGLE_QUOTE) || (s[i] == DOUBLE_QUOTE))
			return (true);
		i++;
	}
	return (false);
}

t_bool	ft_check_eof(t_data *data, char *input, t_heredoc *heredoc)
{
	if ((data == NULL) || (heredoc == NULL))
		return (false);
	if ((input == NULL) && (g_sigint == 0))
	{
		close(heredoc->pipefd[1]);
		ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", heredoc->limiter);
		return (true);
	}
	return (false);
}

t_bool	ft_check_signal(t_data *data, char *input, t_heredoc *heredoc)
{
	(void) input;
	if ((data == NULL) || (heredoc == NULL))
		return (false);
	if (g_sigint == 1)
	{
		data->exit.value = 130;
		close(heredoc->pipefd[1]);
		ft_redir_to_tty(data->tty, STDIN_FILENO);
		return (true);
	}
	return (false);
}

t_bool	ft_check_input(t_data *data, char *input, t_heredoc *heredoc)
{
	size_t	len;
	char	*limiter;

	if ((data == NULL) || (input == NULL) || (heredoc == NULL)
		|| (heredoc->expand == NULL))
		return (true);
	limiter = heredoc->expand;
	len = ft_strlen(limiter);
	if ((ft_strlen(input) == len)
		&& (ft_strncmp(input, limiter, len) == 0))
	{
		close(heredoc->pipefd[1]);
		free(input);
		return (true);
	}
	return (false);
}

t_bool	ft_quotes_in_str(char *input)
{
	size_t	i;

	if (input == NULL)
		return (false);
	i = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == SINGLE_QUOTE) || (input[i] == DOUBLE_QUOTE))
			return (true);
		i++;
	}
	return (false);
}

void	ft_write_heredoc_value(int fd, char *value)
{
	if ((fd < 0) || (value == NULL))
		return ;
	write(fd, value, ft_strlen(value));
}

void	ft_add_heredoc_value(t_data *data, char *input, t_heredoc *heredoc)
{
	char	*value;
	char	*limiter;

	if ((data == NULL) || (input == NULL) || (heredoc == NULL))
		return ;
	limiter = heredoc->limiter;
	if (limiter == NULL)
		return ;
	if (ft_quotes_in_str(limiter))
		write(heredoc->pipefd[1], input, ft_strlen(input));
	else
	{
		ft_expand_heredoc(data, &value, input);
		ft_write_heredoc_value(heredoc->pipefd[1], value);
		free(value);
	}
	write(heredoc->pipefd[1], "\n", 1);
}

void	ft_exec_heredoc(t_data *data, t_heredoc *heredoc)
{
	char	*input;

	if ((data == NULL) || (heredoc == NULL)
		|| (heredoc->limiter == NULL)
		|| (heredoc->expand == NULL))
		return ;
	ft_create_pipe(data, heredoc->pipefd);
	heredoc->is_exec = true;
	while (g_sigint == 0)
	{
		input = readline("> ");
		if (ft_check_signal(data, input, heredoc))
			return ;
		if (ft_check_eof(data, input, heredoc))
			return ;
		if (ft_check_input(data, input, heredoc))
			break ;
		ft_add_heredoc_value(data, input, heredoc);
		free(input); //
	}
	return ;
}

void	ft_get_heredoc(t_data *data, t_cmd *cmd)
{
	t_redir		*redir;
	t_heredoc	*heredoc;

	if ((cmd == NULL) || (cmd->redir == NULL))
		return ;
	redir = cmd->redir;
	while (redir != NULL)
	{
		if ((redir->type == TOKEN_HEREDOC)
			&& (redir->value.heredoc.is_exec == false))
		{
			heredoc = &redir->value.heredoc;
			ft_exec_heredoc(data, heredoc);
		}
		redir = redir->next;
	}
}

void	ft_get_heredoc_value(t_data *data, t_parse *parse)
{
	t_cmd	*cmd;

	if (parse == NULL)
		return ;
	signal(SIGINT, ft_input_handle);
	while (parse != NULL)
	{
		if (parse->type == TOKEN_PIPE)
			parse = parse->next;
		else
		{
			cmd = parse->data.cmd;
			ft_get_heredoc(data, cmd);
			parse = parse->next;
		}
	}
	signal(SIGINT, ft_input_handle);
}

int	ft_check_sigint(void)
{
	if (g_sigint == 1)
	{
		g_sigint = 0;
		return (1);
	}
	return (0);
}

size_t	ft_input_len(t_list *lst)
{
	size_t	len;

	if (lst == NULL)
		return (0);
	len = 0;
	while (lst != NULL)
	{
		len += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (len);
}

void	ft_get_history(char **history_ptr, t_list *temp)
{
	size_t	i;
	size_t	len;
	char	*history;
	size_t	j;

	if ((history_ptr == NULL) || (temp == NULL))
		return ;
	len = ft_input_len(temp);
	history = (char *) malloc((len + 1) * sizeof(char));
	if (history == NULL)
		return ;
	i = 0;
	j = 0;
	while (i < len)
	{
		history[i++] = ((char *) temp->content)[j++];
		if (((char *) temp->content)[j] == '\0')
		{
			temp = temp->next;
			j = 0;
		}
	}
	history[len] = '\0';
	*history_ptr = history;
}

int	ft_parse(t_data *data, t_parse **cmds, char *line, char **history_ptr)
{
	t_token	*token;
	t_parse	*parse;
	t_list	*temp;

	temp = NULL;
	parse = NULL;
	ft_add_content(&temp, line);
	ft_get_token(data, &token, line);
	if (ft_check_token(data, token) != 0)
		return (1);
	ft_get_parse(&parse, token);
	ft_clear_token(&token);
	ft_get_heredoc_value(data, parse);
	if (ft_check_sigint() != 0)
		return (1);
	signal(SIGINT, ft_input_handle);
	ft_get_unclose_pipe(data, &parse, &temp);
	ft_get_history(history_ptr, temp);
	signal(SIGINT, ft_input_handle);
	if (ft_check_sigint() != 0)
		return (1);
	*cmds = parse;
	return (0);
}

static t_bool	ft_last_ispipe(t_parse *parse)
{
	if (parse == NULL)
		return (0);
	while (parse->next != NULL)
		parse = parse->next;
	if (parse->type == TOKEN_PIPE)
		return (1);
	else
		return (0);
}

t_bool	ft_check_input_sigint(t_data *data)
{
	if (data == NULL)
		return (false);
	if (g_sigint == 1)
	{
		data->exit.value = 130;
		ft_redir_to_tty(data->tty, STDIN_FILENO);
		return (true);
	}
	return (false);
}

static void	ft_get_unclose_pipe(t_data *data, t_parse **parse_ptr, t_list **history)
{
	char	*line;
	t_token	*token;
	t_parse	*parse;

	if ((data == NULL) || (parse_ptr == NULL))
		return ;
	parse = *parse_ptr;
	while (ft_last_ispipe(parse))
	{
		signal(SIGINT, ft_input_handle);
		line = ft_readline("> ");
		if (ft_check_input_sigint(data))
			return ;
		if ((line == NULL) && (g_sigint == 0))
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
			data->exit.value = 2;
			return ;
		}
		while (ft_isempty(line))
		{
			free(line);
			line = ft_readline("> ");
			if (ft_check_input_sigint(data))
				return ;
			if ((line == NULL) && (g_sigint == 0))
			{
				ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
				data->exit.value = 2;
				return ;
			}
		}
		ft_add_content(history, ft_strdup(" "));
		ft_add_content(history, line);
		ft_get_token(data, &token, line);
		if (ft_check_token(data, token) != 0)
			return ;
		ft_get_parse(&parse, token);
		ft_clear_token(&token);
		ft_get_heredoc_value(data, parse);
		if (g_sigint == 1)
			return ;
	}
	*parse_ptr = parse;
}
