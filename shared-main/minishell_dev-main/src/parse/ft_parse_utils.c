/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:26:16 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:06 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parse	*ft_new_node(t_type type)
{
	t_parse	*new;

	new = (t_parse *) malloc(sizeof(t_parse));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_parse(t_parse **head_ptr, t_parse *parse)
{
	t_parse	*curr;

	if ((head_ptr == NULL) || (parse == NULL))
		return ;
	if (*head_ptr == NULL)
		*head_ptr = parse;
	else
	{
		curr = *head_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = parse;
		parse->prev = curr;
	}
}
