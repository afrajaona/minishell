/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:41:27 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:30:33 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	ft_s_compare(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (true);
	else
		return (false);
}

void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index)
{
	size_t	i;

	if ((temp == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index + 1;
	while ((s[i] != '\0') && (s[i] != delim))
	{
		ft_add_content(temp, &s[i]);;
		i++;
	}
	ft_add_content(temp, &s[i]);
	*index = i;
}

t_bool	ft_quotes_isclose(char *s, char delim, size_t ldelim_pos)
{
	size_t	i;

	if ((s == NULL) || (ldelim_pos >= ft_strlen(s))
		|| ((ssize_t) ldelim_pos < 0))
		return (false);
	i = ldelim_pos;
	if (s[ldelim_pos] == delim)
		i++;
	while ((s[i] != delim) && (s[i] != '\0'))
		i++;
	if (s[i] == delim)
		return (true);
	else
		return (false);
}

void	ft_clear_lexeme(t_list **lexeme)
{
	t_list	*curr;
	t_list	*next;

	if (lexeme == NULL)
		return ;
	curr = *lexeme;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lexeme = NULL;
}
