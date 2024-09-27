/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:03:02 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:33:33 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

t_expand	*ft_new_expand(t_token_type type, char *value)
{
	t_expand	*expand;

	expand = (t_expand *) malloc(sizeof(t_expand));
	if (new == NULL)
		return (NULL);
	expand->type = type;
	expand->value = value;
	expand->next = NULL;
	return (new);
}

void	ft_add_expand(t_expand **head_p, t_expand **tail_p, t_expand *expand)
{
	t_expand	*tail;

	if (expand == NULL)
		return ;
	tail = *tail_p;
	if (*head_p == NULL)
	{
		*head_p = expand;
		*tail_p = expand;
	}
	else
	{
		tail->next = expand;
		*tail_p = expand;
	}
}
