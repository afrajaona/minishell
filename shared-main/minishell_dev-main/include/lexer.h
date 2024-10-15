/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:39:40 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:12 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "utils.h"

# define LEXEME_PIPE				"|"
# define LEXEME_HEREDOC				"<<"
# define LEXEME_INPUT_REDIR			"<"
# define LEXEME_APPEND				">>"
# define LEXEME_OUTPUT_REDIR		">"

int		ft_get_lexeme(t_list **lexeme_ptr, char *s);
t_bool	ft_s_compare(char *s1, char *s2);
void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index);
t_bool	ft_quotes_isclose(char *s, char delim, size_t ldelim_pos);
void	ft_clear_lexeme(t_list **lexeme);

#endif
