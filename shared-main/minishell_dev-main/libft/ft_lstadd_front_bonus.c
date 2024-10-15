/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:23:02 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:19 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst_ptr, t_list *node)
{
	if ((lst_ptr == NULL) || (node == NULL))
		return ;
	node->next = *lst_ptr;
	*lst_ptr = node;
}
