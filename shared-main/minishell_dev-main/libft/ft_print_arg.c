/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:15:56 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:18 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_arg(const char *format, va_list *ap)
{
	size_t	i;
	int		n;
	t_func	func;

	n = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			func = ft_select_func(format[i]);
			n += ft_call_func(func, format[i], ap);
		}
		else
			n += ft_putchar(format[i]);
		if (format[i] == '\0')
			break ;
		i++;
	}
	return (n);
}
