/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:16:57 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:33:48 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MSH_EXPAND_H
# define FT_MSH_EXPAND_H

# include "minishell.h"

typedef struct s_expand
{
	t_token_type	type;
	char			*value;
	struct s_expand		*next;
}				t_expand;

t_list		*ft_expand_token(t_data *data, t_token_type token, char *s);
char		*ft_expand(t_data *data, char *s);
void		ft_expand_in_quotes(t_data *data, t_list **c, char *s, size_t *i);
void		ft_expand_in_dquotes(t_data *data, t_list **c, char *s, size_t *i);
void		ft_expand_out_quotes(t_data *data, t_list **c, char *s, size_t *i);
void		ft_expand_var(t_data *data, t_list **expand, char *s, size_t *i);
t_bool		ft_quotes_isclose(char *s, char delim, int ldelim_pos);
char		*ft_trim_quotes(char *s);

char		*ft_to_str(t_list *lst);
char		*ft_lst_to_tab(t_list *lst);
void		ft_clear_tmp(t_list **lst);

t_bool		ft_is_var(char *s, size_t pos);
char		*ft_get_varvalue(char *var_name, size_t var_len, char **env);
size_t		ft_envvar_len(char *envvar_name);

t_expand	*ft_new_expand(t_token_type type, char *value);
void		ft_add_expand(t_expand **head_p, t_expand **tail_p, t_expand *lst);

void		ft_print_lst(t_list *lst);
void		ft_print_expand(t_expand *expand);

#endif
