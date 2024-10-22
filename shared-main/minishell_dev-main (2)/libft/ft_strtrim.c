/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:53:51 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:33 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_all_trim(char const *s, char const *set);
static size_t	ft_end_trim_count(char const *s, char const *set);
static size_t	ft_start_trim_count(char const *s, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*strtrim;

	if ((s1 == NULL) || (set == NULL))
		return (NULL);
	start = ft_start_trim_count(s1, set);
	end = ft_end_trim_count(s1, set);
	if (ft_all_trim(s1, set))
		size = 1;
	else if ((start == ft_strlen(s1)) && (end == ft_strlen(s1)))
		size = ft_strlen(s1) + 1;
	else
		size = ft_strlen(s1) - start - end + 1;
	strtrim = (char *) malloc(size * sizeof(char));
	if (strtrim == NULL)
		return (NULL);
	ft_strlcpy(strtrim, (s1 + start), size);
	return (strtrim);
}

static size_t	ft_start_trim_count(char const *s, char const *set)
{
	size_t	n;
	size_t	l;

	n = 0;
	l = ft_strlen(set);
	while (*s && ft_memchr(set, *s, l))
	{
		n++;
		s++;
	}
	return (n);
}

static size_t	ft_end_trim_count(char const *s, char const *set)
{
	size_t	n;
	size_t	set_len;
	size_t	str_len;

	set_len = ft_strlen(set);
	str_len = ft_strlen(s);
	n = 0;
	while ((str_len > 0) && ft_memchr(set, *(s + str_len - 1), set_len))
	{
		n++;
		str_len--;
	}
	return (n);
}

static int	ft_all_trim(char const *s, char const *set)
{
	size_t	i;
	size_t	set_len;

	set_len = ft_strlen(set);
	i = 0;
	while ((s[i] != '\0') && ft_memchr(set, s[i], set_len))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}
