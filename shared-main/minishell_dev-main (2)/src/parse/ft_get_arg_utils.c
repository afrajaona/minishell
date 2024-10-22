/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:41 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:37 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_arg	*ft_new_arg(char *value)
{
	t_arg	*arg;

	arg = (t_arg *) malloc(sizeof(t_arg));
	if (arg == NULL)
		return (NULL);
	arg->value = value;
	arg->next = NULL;
	return (arg);
}

void	ft_arg_add_back(t_arg **arg_ptr, t_arg *arg)
{
	t_arg	*curr;

	if ((arg_ptr == NULL) || (arg == NULL))
		return ;
	if (*arg_ptr == NULL)
		*arg_ptr = arg;
	else
	{
		curr = *arg_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = arg;
	}
}
