/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:20:37 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:02:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ft_print_list(t_list *lst)
{
	char	*s;

	if (lst == NULL)
		ft_printf("NULL\n");
	while (lst != NULL)
	{
		s = (char *) lst->content;
		ft_printf("[%s]\n", s);
		lst = lst->next;
	}
}
