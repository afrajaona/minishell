/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:14:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/26 22:15:07 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "utils.h"

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
	char	*expand; //
	int		heredocfd[2];
}				t_heredoc;

typedef union u_redir_value
{
	t_input_redir	input_redir; //
	t_output_redir	output_redir; //
	t_heredoc	heredoc; //
	t_append	append; //
}		t_redir_value;

typedef struct s_redir
{
	t_type		type;
	t_redir_value	value; //
	struct s_redir	*next;
}		t_redir;

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
	struct s_parse	*next;
	struct s_parse	*prev;
}				t_parse;

#endif
