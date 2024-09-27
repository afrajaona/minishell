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

# define LEXEME_PIPE				"|"
# define LEXEME_HEREDOC				"<<"
# define LEXEME_INPUT_REDIR			"<"
# define LEXEME_APPEND				">>"
# define LEXEME_OUTPUT_REDIR		">"

t_list	*ft_get_lexeme(char *s);

#endif
