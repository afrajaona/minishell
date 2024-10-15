/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:57 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_type	ft_get_type(char *s);
static t_expand	*ft_expand_split_value(t_data *data, t_list *split);

t_list	*ft_expand_split(t_data *data, char *s)
{
	t_expand	*temp;
	t_list		*expand;
	t_list		*split;

	if ((data == NULL) || (s == NULL))
		return (NULL);
	expand = NULL;
	split = ft_split_var(s);
	temp = ft_expand_split_value(data, split);
	expand = ft_join_expand(temp);
	ft_clear_temp_list(&split);
	ft_clear_expand(&temp);
	return (expand);
}

static t_type	ft_get_type(char *s)
{
	t_type	type;

	if ((s[0] == '$') && ft_is_var(s, 0))
		type = TOKEN_VARIABLE;
	else
		type = TOKEN_GENERAL;
	return (type);
}

static t_expand	*ft_expand_split_value(t_data *data, t_list *split)
{
	t_type		type;
	char		*value;
	char		*s;
	t_expand	*expand;
	t_expand	*tail_p;

	ft_expand_init(&expand, &tail_p);
	while (split != NULL)
	{
		s = (char *) split->content;
		type = ft_get_type(s);
		ft_expand(data, &value, s);
		free(s);
		if ((type == TOKEN_VARIABLE) && (value[0] == '\0'))
		{
			free(value);
			split = split->next;
		}
		else
		{
			ft_add_expand(&expand, &tail_p, ft_new_expand(type, value));
			split = split->next;
		}
	}
	return (expand);
}
