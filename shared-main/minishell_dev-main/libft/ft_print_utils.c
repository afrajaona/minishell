/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:04:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:56 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, N);
	return (N);
}

int	ft_putstr(char *str)
{
	int	len;

	if (str == NULL)
		return (ft_putstr(NULL_STR));
	len = 0;
	while (str[len])
		len += ft_putchar(str[len]);
	return (len);
}

int	ft_putnbr(int nbr, int n)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		if (nbr <= -10)
			n += ft_putnbr(-(nbr / 10), n);
		n += N;
		ft_putchar(-(nbr % 10) + '0');
	}
	else
	{
		if (nbr >= 10)
			n += ft_putnbr((nbr / 10), n);
		ft_putchar((nbr % 10) + '0');
	}
	return (n);
}

int	ft_puthex(uintptr_t nbr, int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nbr >= 16)
		n += ft_puthex((nbr / 16), n);
	ft_putchar(hex[nbr % 16]);
	return (n);
}
