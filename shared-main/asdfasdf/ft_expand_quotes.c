/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:35:24 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:29:47 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_expand_in_quotes(t_data *data, t_list **str, char *s, size_t *pos)
{
	size_t	i;

	(void) data;
	i = *pos;
	if (s[i] == SINGLE_QUOTE)
	{
		if (ft_quotes_isclose(s, s[i], i))
		{
			i++;
			while ((s[i] != SINGLE_QUOTE) && (s[i] != '\0'))
			{
				ft_add_content(str, &s[i]);
				i++;
			}
			if ((s[i] == SINGLE_QUOTE) && (s[i] != '\0'))
				i++;
		}
		else
		{
			ft_add_content(str, &s[i]);
			i++;
		}
	}
	*pos = i;
}

void	ft_expand_in_dquotes(t_data *data, t_list **str, char *s, size_t *pos)
{
	size_t	i;

	i = *pos;
	if (s[i] == DOUBLE_QUOTE)
	{
		if (ft_quotes_isclose(s, s[i], i))
		{
			i++;
			while ((s[i] != DOUBLE_QUOTE) && (s[i] != '\0'))
			{
				if (ft_is_var(s, i))
					ft_expand_var(data, str, s, &i);
				else
					ft_add_content(str, &s[i++]);
			}
			if ((s[i] == DOUBLE_QUOTE) && (s[i] != '\0'))
				i++;
		}
		else
			ft_add_content(str, &s[i++]);
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
		ft_add_content(str, &s[i]);
		i++;
	}
	*pos = i;
}
