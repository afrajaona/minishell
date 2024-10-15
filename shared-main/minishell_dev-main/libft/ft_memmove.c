/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:38:56 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:08 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if ((dest == NULL) && (src == NULL))
		return (NULL);
	if ((size_t)((char *) dest - (char *) src) < n)
	{
		while (n > 0)
		{
			i = n - 1;
			((char *) dest)[i] = ((char *) src)[i];
			n--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	return (dest);
}
