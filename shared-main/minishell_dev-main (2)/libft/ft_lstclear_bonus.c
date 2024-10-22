/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:35 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:24 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst_ptr, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if ((lst_ptr == NULL) || (del == NULL))
		return ;
	curr = *lst_ptr;
	while (curr != NULL)
	{
		next = curr->next;
		del(curr->content);
		free(curr);
		curr = next;
	}
	*lst_ptr = NULL;
}
