/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:22:49 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:28 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if ((little_len == 0) || ((little_len == 0) && (len == 0))
		|| (big == little))
		return ((char *) big);
	if (len == 0)
		return (NULL);
	i = 0;
	while ((big[i] != '\0') && (i < len))
	{
		if (big[i] == little[0])
		{
			j = 1;
			while ((big[i + j] == little[j]) && ((i + j) < len)
				&& (big[i + j] != '\0' || little[j] != '\0'))
				j++;
			if (little[j] == '\0')
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
