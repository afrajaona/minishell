/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:12:02 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:33:41 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

char	*ft_expand(t_data *data, char *s)
{
	t_list	*temp;
	size_t	i;
	char	*expand;

	temp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			ft_expand_in_quotes(data, &temp, s, &i);
		else if (s[i] == '\"')
			ft_expand_in_dquotes(data, &temp, s, &i);
		else
			ft_expand_out_quotes(data, &temp, s, &i);
	}
	expand = ft_to_str(temp);
	ft_clear_tmp(&temp);
	return (expand);
}
