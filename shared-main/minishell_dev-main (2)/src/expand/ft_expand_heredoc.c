/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:28:49 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/22 00:28:50 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_expand_heredoc(t_data *data, char **dest, char *src)
{
	size_t	i;
	t_list	*temp;

	if ((data == NULL) || (dest == NULL) || (src == NULL))
		return ;
	temp = NULL;
	i = 0;
	while (src[i] != '\0')
	{
		if (ft_is_var(src, i))
			ft_expand_var(data, &temp, src, &i);
		else
		{
			ft_add_content(&temp, &src[i]);
			i++;
		}
	}
	*dest = ft_to_str(temp);
	ft_clear_temp_list(&temp);
}
