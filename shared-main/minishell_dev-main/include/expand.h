/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:16:57 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:06 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "lexer.h"
# include "builtin.h"
# include "utils.h"

void		ft_expand_token(t_data *data, t_token *token);
t_expand	*ft_get_expand(t_data *data, t_token *token);
void		ft_expand(t_data *data, char **dest, char *src);
t_list		*ft_expand_split(t_data *data, char *s);
void		ft_expand_in_quotes(t_data *data, t_list **c, char *s, size_t *i);
void		ft_expand_in_dquotes(t_data *data, t_list **c, char *s, size_t *i);
void		ft_expand_out_quotes(t_data *data, t_list **c, char *s, size_t *i);
int			ft_trim_quotes(char **dest, char *s);
void		ft_expand_var(t_data *data, t_list **expand, char *s, size_t *i);
t_bool		ft_is_var(char *s, size_t pos);
char		*ft_get_varvalue(char *var_name, size_t var_len, char **env);
size_t		ft_envvar_len(char *envvar_name);
void		ft_expand_init(t_expand **head_ptr, t_expand **tail_ptr);
t_expand	*ft_new_expand(t_type type, char *value);
void		ft_add_expand(t_expand **phead, t_expand **ptail, t_expand *expand);
t_list		*ft_split_var(char *str);
t_list		*ft_join_expand(t_expand *expand);
void		ft_clear_expand(t_expand **expand);
void		ft_clear_temp_expand(t_expand **expand);
t_expand	*ft_get_expand_cmd(t_data *data, char *cmd);
t_expand	*ft_get_expand_arg(t_data *data, char *arg);
t_expand	*ft_get_expand_file(t_data *data, char *file);
t_expand	*ft_get_expand_limter(t_data *data, char *limiter);


#endif
