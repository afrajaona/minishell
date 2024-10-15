/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:54:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:26 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lexer.h"
# include "expand.h"
# include "utils.h"

typedef struct s_flag
{
	t_bool	redir;
	t_bool	cmd;
	t_bool	heredoc;
}				t_flag;

int		ft_get_token(t_data *data, t_token **token, char *line);
int		ft_tokenize(t_token **head_ptr, t_token **tail_ptr, t_list *lexeme);
void	ft_token_init(t_token **head_ptr, t_token **tail_ptr);
t_token	*ft_new_token(t_type type, char *value);
void	ft_add_token(t_token **head_ptr, t_token **tail_ptr, t_token *token);
void	ft_clear_token(t_token **token);
void	ft_flag_init(t_flag *flag);
void	ft_set_flag(t_flag *flag, t_bool redir, t_bool cmd, t_bool heredoc);

#endif
