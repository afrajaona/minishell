/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:01:28 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/30 17:03:57 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index)
{
	size_t	i;

	if ((temp == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index + 1;
	while ((s[i] != '\0') && (s[i] != delim))
	{
		ft_lstadd_back(temp, ft_lstnew(&s[i]));
		i++;
	}
	ft_lstadd_back(temp, ft_lstnew(&s[i]));
	*index = i;
}

void	ft_add_content(t_list **lst, void *content)
{
	ft_lstadd_back(lst, ft_lstnew(content));
}

t_bool	ft_s_compare(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (true);
	else
		return (false);
}
