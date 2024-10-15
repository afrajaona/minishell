/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:53:06 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:11 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	src_len;
	size_t	dst_len;

	if ((dst == NULL) && (size == 0))
		return (0);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	else
	{
		n = size - dst_len - 1;
		dst = dst + dst_len;
		while (*src && (n > 0))
		{
			*dst++ = *src++;
			n--;
		}
		*dst = '\0';
		return (dst_len + src_len);
	}
}
