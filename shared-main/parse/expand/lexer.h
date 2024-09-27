/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:39:40 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/30 16:39:42 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "utils.h"

t_bool	ft_quotes_isclose(char *s, char delim, size_t ldelim_pos);
void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index);

#endif
