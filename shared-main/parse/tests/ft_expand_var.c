/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:39:47 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/22 11:04:44 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

static char	*ft_get_varname(char *s, size_t pos);
static void	ft_add_varvalue(t_data *data, t_list **s, char *name, size_t *i);

void	ft_expand_var(t_data *data, t_list **expand, char *s, size_t *index)
{
	size_t	i;
	char	*var_name;

	var_name = NULL;
	i = *index;
	if (ft_is_var(s, i))
	{
		i++;
		var_name = ft_get_varname(s, i);
		ft_add_varvalue(data, expand, var_name, &i);
	}
	free(var_name);
	*index = i;
}

static char	*ft_get_varname(char *s, size_t pos)
{
	size_t	i;
	t_list	*temp;
	char	*var_name;

	i = pos;
	temp = NULL;
	if ((ft_isalpha(s[i]) == false) && (s[i] != '_') && s[i] != '?')
		return (NULL);
	if (s[i] == '?')
		ft_lstadd_back(&temp, ft_lstnew(&s[i]));
	else
	{
		while ((ft_isalpha(s[i]) || ft_isdigit(s[i]) || (s[i] == '_'))
			&& (s[i] != '\0'))
		{
			ft_lstadd_back(&temp, ft_lstnew(&s[i]));
			i++;
		}
	}
	var_name = ft_to_str(temp);
	ft_clear_tmp(&temp);
	return (var_name);
}

static void	ft_add_varvalue(t_data *data, t_list **str, char *name, size_t *i)
{
	int		j;
	char	*var_value;
	size_t	var_len;

	if (name == NULL)
		return ;
	var_len = ft_strlen(name);
	if ((name[0] == '?') && (ft_strlen("?") == var_len))
		var_value = data->exit;
	else
		var_value = ft_get_varvalue(name, var_len, data->env);
	j = 0;
	while ((var_value != NULL) && (var_value[j] != '\0'))
	{
		ft_lstadd_back(str, ft_lstnew(&var_value[j]));
		j++;
	}
	*i = *i + var_len;
}
