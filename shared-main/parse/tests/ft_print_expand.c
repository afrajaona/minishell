/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:33:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:34:03 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

static void	ft_print_expand_type(int type);

void	ft_print_lst(t_list *lst)
{
	char	*s;

	s = NULL;
	if (lst == NULL)
	{
		ft_printf(": NULL\n");
		return ;
	}
	while (lst != NULL)
	{
		s = (char *) lst->content;
		ft_printf(": [%s]\n", s);
		lst = lst->next;
	}
}

void	ft_print_expand(t_expand *expand)
{
	if (expand == NULL)
	{
		ft_printf("{NULL}\n");
		return ;
	}
	while (expand != NULL)
	{
		ft_printf("{[%s] : ", expand->value);
		ft_print_expand_type(expand->type);
		ft_printf("} ");
		expand = expand->next;
	}
	ft_printf("\n");
}

static void	ft_print_expand_type(int type)
{
	if (type == TOKEN_VAR)
		ft_printf("VAR");
	else
		ft_printf("STR");
}
