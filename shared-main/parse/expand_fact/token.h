/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:54:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/02 18:52:40 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "expand.h"
# include "lexer.h"
# include "utils.h"

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

typedef struct s_flag
{
	t_bool	redir;
	t_bool	cmd;
	t_bool	heredoc;
}				t_flag;

typedef struct s_token
{
	t_type			type;
	char			*value;
	t_expand		*expand;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

int		ft_tokenize(t_token **head_ptr, t_token **tail_ptr, t_list *lexeme);
void	ft_token_init(t_token **head_ptr, t_token **tail_ptr);
t_token	*ft_new_token(t_type type, char *value);
void	ft_add_token(t_token **head_ptr, t_token **tail_ptr, t_token *token);
void	ft_clear_token(t_token **token);
void	ft_flag_init(t_flag *flag);
void	ft_set_flag(t_flag *flag, t_bool redir, t_bool cmd, t_bool heredoc);

#endif
