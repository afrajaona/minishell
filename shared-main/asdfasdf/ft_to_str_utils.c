/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:31 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:30:48 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_add_content(t_list **lst, void *content)
{
	ft_lstadd_back(lst, ft_lstnew(content));
}

char	*ft_lst_to_tab(t_list *lst)
{
	int		i;
	char	*tab;
	int		len;

	len = ft_lstsize(lst);
	tab = (char *) malloc((len + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = *((char *) lst->content);
		lst = lst->next;
		i++;
	}
	tab[len] = '\0';
	if (tab[0] == '\0')
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	*ft_to_str(t_list *lst)
{
	int		i;
	char	*tab;
	int		len;

	len = ft_lstsize(lst);
	tab = (char *) malloc((len + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = *((char *) lst->content);
		lst = lst->next;
		i++;
	}
	tab[len] = '\0';
	return (tab);
}

void	ft_clear_tmp(t_list **lst)
{
	t_list	*next;
	t_list	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
