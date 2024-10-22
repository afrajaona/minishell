/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:26:00 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:51 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_get_parse(t_parse **parse_ptr, t_token *token)
{
	t_parse	*temp;

	temp = NULL;
	if ((parse_ptr == NULL) || (token == NULL))
		return ;
	while (token != NULL)
	{
		if (token->type == TOKEN_PIPE)
			ft_add_pipe_node(&temp, &token);
		else
			ft_add_cmd_node(&temp, &token);
	}
	ft_add_parse(parse_ptr, temp);
}
