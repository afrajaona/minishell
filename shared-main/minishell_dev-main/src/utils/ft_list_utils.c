/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:26:58 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:34 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_clear_list(t_list **lst)
{
	t_list	*next;
	t_list	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	ft_clear_temp_list(t_list **lst)
{
	t_list	*next;
	t_list	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
