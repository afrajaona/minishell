/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_expand_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:24:01 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:35 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	ft_add_file_val(t_list *split, t_expand **head, t_expand **tail);

t_expand	*ft_get_expand_file(t_data *data, char *file)
{
	t_expand	*expand;
	t_expand	*tail_p;
	t_list		*split;

	ft_expand_init(&expand, &tail_p);
	split = ft_expand_split(data, file);
	ft_add_file_val(split, &expand, &tail_p);
	ft_clear_temp_list(&split);
	return (expand);
}

static void	ft_add_file_val(t_list *split, t_expand **head, t_expand **tail)
{
	char		*value;
	t_expand	*expand;

	if ((split == NULL) || (head == NULL) || (tail == NULL))
		return ;
	while (split != NULL)
	{
		value = (char *) split->content;
		expand = ft_new_expand(TOKEN_FILE, value);
		ft_add_expand(head, tail, expand);
		split = split->next;
	}
}
