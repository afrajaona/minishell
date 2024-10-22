/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:44:27 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(va_list *ap)
{
	void		*ptr;
	uintptr_t	nbr;

	ptr = va_arg(*ap, void *);
	if (ptr == NULL)
		return (ft_putstr(NULL_PTR));
	nbr = (uintptr_t) ptr;
	return (ft_putstr(ADDR_PRE) + ft_puthex(nbr, N));
}
