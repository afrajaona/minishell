/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:17:19 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:31 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putlhex(unsigned int nbr, int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nbr >= 16)
		n += ft_putlhex((nbr / 16), n);
	ft_putchar(hex[nbr % 16]);
	return (n);
}

int	ft_print_lhex(va_list *ap)
{
	unsigned int	nbr;

	nbr = va_arg(*ap, unsigned int);
	return (ft_putlhex(nbr, N));
}
