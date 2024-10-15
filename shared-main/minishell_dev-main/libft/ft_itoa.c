/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:06:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:59:38 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblen(int n);

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	size;
	char	*str;

	size = ft_nblen(n) + 1;
	str = (char *) malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	i = size - 2;
	while (n != 0)
	{
		if (n < 0)
			str[i] = -(n % 10) + '0';
		else
			str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	str[size - 1] = '\0';
	return (str);
}

static size_t	ft_nblen(int n)
{
	size_t	len;

	len = 0;
	if ((n == 0) || (n < 0))
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
