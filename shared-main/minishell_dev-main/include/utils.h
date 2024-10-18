/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:56:45 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:31 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

# define PROMPT					"minishell> "

# define TOKEN_COMMAND			1
# define TOKEN_ARGUMENT			2
# define TOKEN_PIPE				3
# define TOKEN_HEREDOC			4
# define TOKEN_APPEND			5
# define TOKEN_INPUT_REDIR		6
# define TOKEN_OUTPUT_REDIR		7
# define TOKEN_FILE				8
# define TOKEN_LIMITER			9
# define TOKEN_GENERAL			10
# define TOKEN_VARIABLE			11

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'

typedef int	t_type;

extern int	g_sigint;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_expand
{
	t_type			type;
	char			*value;
	struct s_expand	*next;
}				t_expand;

typedef struct s_token
{
	t_type			type;
	char			*value;
	t_expand		*expand;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

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
	char	*expand;
	int		pipefd[2];
}				t_heredoc;

typedef union u_redir_value
{
	t_input_redir	input_redir;
	t_output_redir	output_redir;
	t_heredoc		heredoc;
	t_append		append;
}		t_redir_value;

typedef struct s_redir
{
	t_type			type;
	t_redir_value	value;
	struct s_redir	*next;
}		t_redir;

typedef struct s_cmd
{
	pid_t		pid;
	char		*value;
	t_redir		*redir;
	t_arg		*arg;
}				t_cmd;

typedef struct s_pipe
{
	int	pipe_id;
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

typedef struct s_exit
{
	int		value;
	t_list	*conv_addr;
}		t_exit;

typedef struct s_exec
{
	char	*value;
	char	**argv;
}		t_exec;

typedef struct s_data
{
	char	*tty;
	t_exit	exit;
	char	**env;
	char	**ex_var;
}				t_data;

void	ft_add_content(t_list **lst, void *content);
char	*ft_lst_to_tab(t_list *lst);
char	*ft_to_str(t_list *lst);
void    ft_clear_cmd(t_cmd *cmd);
void	ft_clear_list(t_list **lst);
void	ft_clear_temp_list(t_list **lst);
void	ft_init_data(t_data *data, int ac, char **av, char **env);
void	ft_free_data(t_data *data);
void	ft_clear_tab(char **tab);
char	**ft_tab_dup(char **tab);
char    **ft_to_tab(t_list *lst);
void    ft_clear_list(t_list **lst);
void    ft_clear_temp_list(t_list **lst);
void	ft_input_handle(int signal);
void	ft_sigint_handle(int signal);
void	ft_set_signal(void);
void    ft_set_default_signal(void);
int	ft_redir_to_tty(t_data *data);

#endif
