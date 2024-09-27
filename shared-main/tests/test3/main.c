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

#include <stdio.h>
#include "libft.h"

#define TOKEN_COMMAND			1
#define TOKEN_ARGUMENT			2
#define TOKEN_PIPE				3
#define TOKEN_HEREDOC			4
#define TOKEN_APPEND			5
#define TOKEN_INPUT_REDIR		6
#define TOKEN_OUTPUT_REDIR		7
#define TOKEN_FILE				8
#define TOKEN_LIMITER			9
#define TOKEN_GENERAL			10
#define TOKEN_VARIABLE			11

#define SINGLE_QUOTE			'\''
#define DOUBLE_QUOTE			'\"'

typedef int	t_type;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}				t_arg;

typedef struct s_input_redir
{
	int		n_arg;
	char	*filename;
	t_list	*expand;
}				t_input_redir;

typedef struct s_output_redir
{
	int		n_arg;
	char	*filename;
	t_list	*expand;
}				t_output_redir;

typedef struct s_append
{
	int		n_arg;
	char	*filename;
	t_list	*expand;
}				t_append;

typedef struct s_heredoc
{
	t_bool	is_exec;
	char	*limiter;
	int		heredocfd[2];
}				t_heredoc;

typedef union u_input_value
{
	t_input_redir	*input_redir;
	t_heredoc		*heredoc;
}				t_input_value;

typedef union u_output_value
{
	t_output_redir	*output_redir;
	t_append		*append;
}				t_output_value;

typedef struct s_input
{
	t_type			type;
	t_input_value	value;
	struct s_input	*next;
}				t_input;

typedef struct s_output
{
	t_type			type;
	t_output_value	data;
	struct s_output	*next;
}				t_output;

typedef	union	u_data
{
	t_input_value	*input_value;
	t_output_value	*output_value;
	t_append	*append;
	t_heredoc	*heredoc;
}	t_data;

typedef	struct	s_redir
{
	t_type		type;
	t_data		*data;
}	t_redir;

typedef struct s_cmd
{
	char		*value;
	t_redir		*redir;
	t_arg		*arg;
}				t_cmd;

typedef struct s_pipe
{
	int	pipefd[2];
}				t_pipe;

typedef union u_parse_value
{
	t_cmd	*cmd;
	t_pipe	*pipe;
}			t_parse_value;


typedef struct s_parse
{
	t_type			type;
	t_parse_value	data;
	struct s_node	*next;
	struct s_node	*prev;
}				t_parse;

int	main(void)
{
	t_input_redir	redir;
	t_input		input;
	t_cmd		command;
	t_arg		argument;
	t_cmd		*cmd;

	cmd = &command;

	redir.n_arg = 1;
	redir.filename = "infile";
	redir.expand = NULL;

	input.type = TOKEN_INPUT_REDIR;
	input.value.input_redir = &redir;
	input.next = NULL;

	argument.value = "-e";
	argument.next = NULL;

	cmd->value = "cat";
	cmd->input = &input;
	cmd->output = NULL;
	cmd->arg = &argument;

	printf("node value: %s\n", cmd->value);
	printf("input value: %s\n", cmd->input->value.input_redir->filename);
	printf("argument value: %s\n", cmd->arg->value);
	return (0);
}
