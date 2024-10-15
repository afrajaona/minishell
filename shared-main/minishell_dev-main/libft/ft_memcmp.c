/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:41:54 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:58 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*str1;
	const char	*str2;
	int			diff;

	str1 = (const char *) s1;
	str2 = (const char *) s2;
	diff = 0;
	i = 0;
	while ((diff == 0) && (i < n))
	{
		diff = (unsigned char) str1[i] - (unsigned char) str2[i];
		i++;
	}
	return (diff);
}
