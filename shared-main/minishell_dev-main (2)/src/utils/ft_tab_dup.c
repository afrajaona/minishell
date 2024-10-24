/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:27:05 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/24 13:50:01 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_clear_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_tab_dup(char **tab)
{
	size_t	len;
	char	**dup;
	size_t	i;

	len = 0;
	while (tab[len] != NULL)
		len++;
	dup = (char **) malloc((len + 1) * sizeof(char *));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(tab[i]);
		if (dup[i] == NULL)
		{
			ft_clear_tab(dup);
			return (NULL);
		}
		i++;
	}
	dup[len] = NULL;
	return (dup);
}
