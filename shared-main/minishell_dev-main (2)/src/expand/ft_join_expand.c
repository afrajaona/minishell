/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:25:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:53 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	ft_join_var(t_list **join, t_list **tmp, char *s, t_expand *expand);
static void	ft_join_str(t_list **join, t_list **tmp, char *s, t_expand *expand);

t_list	*ft_join_expand(t_expand *expand)
{
	t_list	*join;
	t_list	*temp;
	char	*str;

	join = NULL;
	temp = NULL;
	while (expand != NULL)
	{
		str = expand->value;
		ft_join_var(&join, &temp, str, expand);
		ft_join_str(&join, &temp, str, expand);
		expand = expand->next;
	}
	if (temp)
	{
		ft_add_content(&join, ft_to_str(temp));
		ft_clear_temp_list(&temp);
	}
	return (join);
}

static void	ft_join_var(t_list **join, t_list **temp, char *s, t_expand *expand)
{
	size_t	i;

	if (expand->type == TOKEN_VARIABLE)
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (ft_isspace(s[i]))
			{
				if (*temp)
				{
					ft_add_content(join, ft_to_str(*temp));
					ft_clear_temp_list(temp);
				}
				while (ft_isspace(s[i]) && (s[i] != '\0'))
					i++;
			}
			else
			{
				ft_add_content(temp, &s[i]);
				i++;
			}
		}
	}
}

static void	ft_join_str(t_list **join, t_list **temp, char *s, t_expand *expand)
{
	size_t	i;

	if (expand->type == TOKEN_GENERAL)
	{
		if ((s[0] == '\0') && (expand->next == NULL))
		{
			ft_add_content(join, ft_to_str(*temp));
			ft_clear_temp_list(temp);
		}
		i = 0;
		while (s[i] != '\0')
		{
			ft_add_content(temp, &s[i]);
			i++;
		}
	}
}
