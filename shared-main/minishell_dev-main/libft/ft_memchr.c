/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:41:15 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:54 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*str;

	str = (const char *) s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (char) c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
