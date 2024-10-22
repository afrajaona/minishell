/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:18:18 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 00:59:55 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "utils.h"

void	ft_print_expand(t_expand *expand);
void	ft_print_list(t_list *lst);
void	ft_print_parse(t_parse *parse);
void	ft_print_parse_debug(t_parse *parse);
void	ft_print_type(int type);
void	ft_print_token(t_token *token);
char	*ft_readline(const char *prompt);

#endif
