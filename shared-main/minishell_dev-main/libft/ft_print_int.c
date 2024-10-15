/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:22:12 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:27 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_int(va_list *ap)
{
	int	nbr;

	nbr = va_arg(*ap, int);
	return (ft_putnbr(nbr, N));
}
