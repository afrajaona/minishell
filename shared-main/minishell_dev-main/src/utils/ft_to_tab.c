/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:27:17 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:48 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_to_tab(t_list *lst)
{
	size_t	i;
	char	**tab;
	size_t	len;

	len = ft_lstsize(lst);
	tab = (char **) malloc((len + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[len] = NULL;
	i = 0;
	while (i < len)
	{
		tab[i] = (char *) lst->content;
		lst = lst->next;
		i++;
	}
	return (tab);
}
