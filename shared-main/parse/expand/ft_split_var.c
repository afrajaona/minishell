/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:27:06 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/06 22:27:16 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	ft_add_general_str(t_list **split, char *s, size_t *index);
static void	ft_add_variable(t_list **split, char *s, size_t *index);

t_list	*ft_split_var(char *str)
{
	size_t	i;
	t_list	*split;

	split = NULL;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ft_add_general_str(&split, str, &i);
		ft_add_variable(&split, str, &i);
	}
	return (split);
}

static void	ft_add_general_str(t_list **split, char *s, size_t *index)
{
	size_t	i;
	t_list	*temp;

	temp = NULL;
	if ((split == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index;
	while ((ft_is_var(s, i) == false) && s[i] != '\0')
	{
		ft_add_content(&temp, &s[i]);
		if (((s[i] == SINGLE_QUOTE) || (s[i] == DOUBLE_QUOTE))
			&& ft_quotes_isclose(s, s[i], i))
			ft_add_str_in_delim(&temp, s, s[i], &i);
		if (s[i] != '\0')
			i++;
		if ((s[i] == '\0') || ft_is_var(s, i))
		{
			ft_add_content(split, ft_lst_to_tab(temp));
			ft_clear_tmp(&temp);
		}
	}
	*index = i;
}

static void	ft_add_variable(t_list **split, char *s, size_t *index)
{
	size_t	i;
	t_list	*temp;

	temp = NULL;
	if ((split == NULL) || (s == NULL) || (index == NULL))
		return ;
	i = *index;
	if (ft_is_var(s, i) && (s[i] != '\0'))
	{
		ft_add_content(&temp, &s[i++]);
		if (s[i] == '?')
			ft_add_content(&temp, &s[i++]);
		else
		{
			while ((ft_isalpha(s[i]) || ft_isdigit(s[i]) || (s[i] == '_'))
				&& (s[i] != '\0'))
				ft_add_content(&temp, &s[i++]);
		}
		ft_add_content(split, ft_lst_to_tab(temp));
		ft_clear_tmp(&temp);
	}
	*index = i;
}
