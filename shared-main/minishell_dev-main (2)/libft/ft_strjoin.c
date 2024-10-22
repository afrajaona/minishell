/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:54:09 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:07 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*join;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *) malloc(size * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, size);
	return (join);
}
