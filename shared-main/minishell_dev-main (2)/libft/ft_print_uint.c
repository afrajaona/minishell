/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:19:04 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:53 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putunbr(unsigned int nbr, int n)
{
	if (nbr >= 10)
		n += ft_putunbr((nbr / 10), n);
	ft_putchar((nbr % 10) + '0');
	return (n);
}

int	ft_print_uint(va_list *ap)
{
	unsigned int	nbr;

	nbr = va_arg(*ap, unsigned int);
	return (ft_putunbr(nbr, N));
}
