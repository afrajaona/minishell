/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:04:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:21:19 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_call_func(t_func func, char conv, va_list *ap)
{
	int	n;

	n = 0;
	if (func == NULL)
	{
		n += ft_putchar('%');
		n += ft_putchar(conv);
	}
	else
		n = func(ap);
	return (n);
}
