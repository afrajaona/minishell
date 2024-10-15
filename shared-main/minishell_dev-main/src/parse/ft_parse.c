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

/*static t_bool	ft_last_ispipe(t_parse *parse);
static void		ft_handle_line_error(char *line);
static void		ft_get_unclose_pipe(t_data *data, t_parse **parse_ptr);*/

int	g_sigint = 0;

int	ft_exec_heredoc(t_heredoc *heredoc)
{
	char	*input;
	char	*limiter;

	if (heredoc == NULL)
		return (-1);
	if (pipe(heredoc->pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	limiter = heredoc->expand;
	ft_printf("Test heredoc (%s):\n", limiter);
	while (1)
	{
		input = readline("> ");
		if (g_sigint == 1)
		{
			close(heredoc->pipefd[1]);
			return (0);
		}
		if ((input == NULL) && (g_sigint == 0))
		{
			heredoc->is_exec = true;
			close(heredoc->pipefd[1]);
			ft_printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", heredoc->limiter);
			return (1);
		}
		if ((ft_strlen(input) == ft_strlen(limiter))
			&& (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
		{
			heredoc->is_exec = true;
			free(input);
			close(heredoc->pipefd[1]);
			break ;
		}
		write(heredoc->pipefd[1], input, ft_strlen(input));
		write(heredoc->pipefd[1], "\n", 1);
		free(input);
	}
	return (0);
}

void	ft_heredoc(t_heredoc *heredoc)
{
	signal(SIGINT, ft_input_handle);
	ft_exec_heredoc(heredoc);
	signal(SIGINT, ft_sigint_handle);
}

int	ft_parse(t_data *data, t_parse **cmds, char *line)
{
	t_token	*token;
	t_parse	*parse;

	//t_heredoc	test; //
	//char		*s; //

	//test.limiter = "eof"; //
	//test.expand = "eof"; //

	parse = NULL;
	ft_get_token(data, &token, line);
	// todo: check token
	ft_get_parse(&parse, token);
	ft_clear_token(&token);
	// todo: exec here_doc
	//ft_heredoc(&test); //
	//ft_redir_to_tty(data); //

	// Print heredoc result
	/*ft_printf("Heredoc content\n");
	ft_printf("{\n");
	s = get_next_line(test.pipefd[0]);
	while (s != NULL)
	{
		ft_printf("%s", s);
		s = get_next_line(test.pipefd[0]);
	}
	ft_printf("}\n");*/

	// todo: check redir
	//ft_get_unclose_pipe(data, &parse);
	free(line);
	*cmds = parse;
	return (0);
}

/*
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

static void	ft_handle_line_error(char *line)
{
	if (line == NULL)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		exit(2);
	}
}


static void	ft_get_unclose_pipe(t_data *data, t_parse **parse_ptr)
{
	char	*line;
	t_token	*token;
	t_parse	*parse;

	if ((data == NULL) || (parse_ptr == NULL))
		return ;
	parse = *parse_ptr;
	while (ft_last_ispipe(parse))
	{
		line = ft_readline("> ");
		ft_handle_line_error(line);
		while (ft_isempty(line))
		{
			free(line);
			line = ft_readline("> ");
			ft_handle_line_error(line);
		}
		ft_get_token(data, &token, line);
		// todo: check token
		ft_get_parse(&parse, token);
		ft_clear_token(&token);
		// todo: exec here_doc
		// todo: check redir
		free(line);
	}
	*parse_ptr = parse;
}*/
