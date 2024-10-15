/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:14:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:22 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include "token.h"
# include "debug.h"

int	ft_parse(t_data *data, t_parse **cmds, char *line);
void	ft_get_parse(t_parse **parse_ptr, t_token *token);
t_parse	*ft_new_node(t_type type);
void	ft_add_parse(t_parse **head_ptr, t_parse *parse);
void	ft_add_cmd_node(t_parse **parse_ptr, t_token **token_ptr);
t_cmd	*ft_new_cmd(void);
t_pipe	*ft_new_pipe(void);
void	ft_next_token(t_token **token_ptr, t_type type);
void	ft_add_pipe_node(t_parse **parse_ptr, t_token **token_ptr);
t_arg	*ft_new_arg(char *value);
void	ft_arg_add_back(t_arg **arg_ptr, t_arg *arg);
void	ft_get_arg_value(t_cmd *cmd, t_token **token_ptr);
void	ft_get_cmd_value(t_cmd *cmd, t_token **token_ptr);
void	ft_add_input_redir(t_cmd *cmd, t_token **token_ptr);
void	ft_add_output_redir(t_cmd *cmd, t_token **token_ptr);
void	ft_add_heredoc_redir(t_cmd *cmd, t_token **token_ptr);
void	ft_add_append_redir(t_cmd *cmd, t_token **token_ptr);
t_redir	*ft_new_redir(t_token *token, t_type type);
void	ft_redir_add_back(t_redir **redir_ptr, t_redir *redir);
int		ft_get_redir_value(t_redir *redir, t_type type, t_token *token);
int		ft_get_input_redir(t_redir *redir, t_type type, t_token *token);
int		ft_get_output_redir(t_redir *redir, t_type type, t_token *token);
int		ft_get_append_redir(t_redir *redir, t_type type, t_token *token);
int		ft_get_heredoc_redir(t_redir *redir, t_type type, t_token *token);
t_bool	ft_check_parse(t_parse *parse);

#endif
