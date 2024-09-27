/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:35:24 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:33:02 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

void	ft_expand_in_quotes(t_data *data, t_list **str, char *s, size_t *pos)
{
	size_t	i;

	(void) data;
	i = *pos;
	if (s[i] == '\'')
	{
		if (ft_quotes_isclose(s, s[i], i))
		{
			i++;
			while ((s[i] != '\'') && (s[i] != '\0'))
			{
				ft_lstadd_back(str, ft_lstnew(&s[i]));
				i++;
			}
			if (s[i] == '\'')
				i++;
		}
		else
		{
			ft_lstadd_back(str, ft_lstnew(&s[i]));
			i++;
		}
	}
	*pos = i;
}

void	ft_expand_in_dquotes(t_data *data, t_list **str, char *s, size_t *pos)
{
	size_t	i;

	i = *pos;
	if (s[i] == '\"')
	{
		if (ft_quotes_isclose(s, s[i], i))
		{
			i++;
			while ((s[i] != '\"') && (s[i] != '\0'))
			{
				if (ft_is_var(s, i))
					ft_expand_var(data, str, s, &i);
				else
					ft_lstadd_back(str, ft_lstnew(&s[i++]));
			}
			if (s[i] == '\"')
				i++;
		}
		else
			ft_lstadd_back(str, ft_lstnew(&s[i++]));
	}
	*pos = i;
}

void	ft_expand_out_quotes(t_data *data, t_list **str, char *s, size_t *pos)
{
	size_t	i;

	i = *pos;
	if (ft_is_var(s, i))
		ft_expand_var(data, str, s, &i);
	else
	{
		ft_lstadd_back(str, ft_lstnew(&s[i]));
		i++;
	}
	*pos = i;
}

t_bool	ft_quotes_isclose(char *s, char delim, int ldelim_pos)
{
	int	i;

	i = ldelim_pos + 1;
	while ((s[i] != delim) && (s[i] != '\0'))
		i++;
	if (s[i] == delim)
		return (true);
	else
		return (false);
}
