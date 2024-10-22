/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:05:17 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:42:29 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_func	ft_select_func(char conv)
{
	t_func	select;

	if (conv == 'c')
		select = ft_print_char;
	else if (conv == 's')
		select = ft_print_str;
	else if (conv == 'p')
		select = ft_print_ptr;
	else if (conv == 'd')
		select = ft_print_int;
	else if (conv == 'i')
		select = ft_print_int;
	else if (conv == 'u')
		select = ft_print_uint;
	else if (conv == 'x')
		select = ft_print_lhex;
	else if (conv == 'X')
		select = ft_print_uhex;
	else if (conv == '%')
		select = ft_print_percent;
	else
		select = NULL;
	return (select);
}
