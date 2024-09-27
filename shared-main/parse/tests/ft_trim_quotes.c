/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:15:51 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:34:13 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	ft_get_str(t_list **temp, char *s, char delim, size_t *index);

int	ft_trim_quotes(char **dest, char *s)
{
	size_t	i;
	t_list	*temp;

	if ((dest == NULL) || (s == NULL))
		return (-1);
	temp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
			&& ft_quotes_isclose(s, s[i], i))
			ft_get_str(&temp, s, s[i], &i);
		else
		{
			ft_add_content(&temp, &s[i]);
			i++;
		}
	}
	*dest = ft_to_str(temp);
	ft_clear_tmp(&temp);
	return (0);
}

static void	ft_get_str(t_list **temp, char *s, char delim, size_t *index)
{
	size_t	i;

	i = *index + 1;
	while ((s[i] != delim) && (s[i] != '\0'))
	{
		ft_add_content(temp, &s[i]);
		i++;
	}
	if ((s[i] == delim) && (s[i] != '\0'))
		i++;
	*index = i;
}
