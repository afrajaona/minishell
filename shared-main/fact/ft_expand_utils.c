/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:03:02 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:30:05 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_expand_init(t_expand **head_ptr, t_expand **tail_ptr)
{
	*head_ptr = NULL;
	*tail_ptr = NULL;
}

t_expand	*ft_new_expand(t_type type, char *value)
{
	t_expand	*expand;

	expand = (t_expand *) malloc(sizeof(t_expand));
	if (expand == NULL)
		return (NULL);
	expand->type = type;
	expand->value = value;
	expand->next = NULL;
	return (expand);
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
