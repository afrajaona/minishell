/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:38:26 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:42:19 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		if (n <= -10)
			ft_putnbr_fd(-(n / 10), fd);
		c = -(n % 10) + '0';
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd((n / 10), fd);
		c = (n % 10) + '0';
	}
	write(fd, &c, 1);
}
