/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:08:15 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:36 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		size = 1;
	else if (len > (ft_strlen(s) - start))
		size = ft_strlen(s) - start + 1;
	else
		size = len + 1;
	substr = (char *) malloc(size * sizeof(char));
	if (substr == NULL)
		return (NULL);
	if (start <= ft_strlen(s))
		ft_memcpy(substr, (s + start), (size - 1));
	substr[size - 1] = '\0';
	return (substr);
}
