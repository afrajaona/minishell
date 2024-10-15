/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_expand_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:23:51 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:27 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	ft_add_arg_val(t_list *split, t_expand **head_p, t_expand **tail_p);

t_expand	*ft_get_expand_arg(t_data *data, char *arg)
{
	t_expand	*expand;
	t_expand	*tail_p;
	t_list		*split;

	ft_expand_init(&expand, &tail_p);
	split = ft_expand_split(data, arg);
	ft_add_arg_val(split, &expand, &tail_p);
	ft_clear_temp_list(&split);
	return (expand);
}

static void	ft_add_arg_val(t_list *split, t_expand **head_p, t_expand **tail_p)
{
	char		*value;
	t_expand	*expand;

	if ((split == NULL) || (head_p == NULL) || (tail_p == NULL))
		return ;
	while (split != NULL)
	{
		value = (char *) split->content;
		expand = ft_new_expand(TOKEN_ARGUMENT, value);
		ft_add_expand(head_p, tail_p, expand);
		split = split->next;
	}
}
