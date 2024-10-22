/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:12:02 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:22 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_expand(t_data *data, char **dest, char *src)
{
	size_t	i;
	t_list	*temp;

	if ((data == NULL) || (src == NULL) || (dest == NULL))
		return ;
	temp = NULL;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == SINGLE_QUOTE)
			ft_expand_in_quotes(data, &temp, src, &i);
		else if (src[i] == DOUBLE_QUOTE)
			ft_expand_in_dquotes(data, &temp, src, &i);
		else
			ft_expand_out_quotes(data, &temp, src, &i);
	}
	*dest = ft_to_str(temp);
	ft_clear_temp_list(&temp);
}
