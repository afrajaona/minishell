/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:20:34 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:47 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putuhex(unsigned int nbr, int n)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (nbr >= 16)
		n += ft_putuhex((nbr / 16), n);
	ft_putchar(hex[nbr % 16]);
	return (n);
}

int	ft_print_uhex(va_list *ap)
{
	unsigned int	nbr;

	nbr = va_arg(*ap, unsigned int);
	return (ft_putuhex(nbr, N));
}
