/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:25:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:10 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst_ptr, t_list *node)
{
	t_list	*last;

	if ((lst_ptr == NULL) || (node == NULL))
		return ;
	if (*lst_ptr == NULL)
		*lst_ptr = node;
	else
	{
		last = ft_lstlast(*lst_ptr);
		last->next = node;
	}
}
