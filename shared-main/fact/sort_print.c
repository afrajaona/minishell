/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:25:18 by arajaona          #+#    #+#             */
/*   Updated: 2024/07/11 11:50:09 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	print_export_format(char **s)
{
	int	i;
	int	j;
	char	*tmp;
	
	i = -1;
	while (s[++i])
	{
		j = 0;
		while (s[i][j] && s[i][j] != '=')
			j++;
		if (s[i][j])
		{
			tmp = ft_substr(s[i], 0, j + 1);
			printf("declare -x %s\"%s\"\n", tmp, &s[i][j + 1]);
			free (tmp);
		}
		else
			printf("declare -x %s\n", s[i]);
	}
}

void	sort_print(char **tab)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_tab_dup(tab);
	i = 0;
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strncmp(tmp[i], tmp[j], ft_strlen(tmp[i])) > 0)
				ft_swap(&tmp[i], &tmp[j]);
			j++;
		}
		i++;
	}
	print_export_format(tmp);
	free_tab(tmp);
}
