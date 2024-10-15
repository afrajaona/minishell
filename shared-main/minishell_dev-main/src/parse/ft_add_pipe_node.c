/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_pipe_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:03 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:23 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_add_pipe_node(t_parse **parse_ptr, t_token **token_ptr)
{
	t_parse	*node;

	node = ft_new_node(TOKEN_PIPE);
	if (node == NULL)
	{
		ft_next_token(token_ptr, TOKEN_PIPE);
		return ;
	}
	node->data.pipe = ft_new_pipe();
	if (node->data.pipe == NULL)
	{
		free(node);
		ft_next_token(token_ptr, TOKEN_PIPE);
		return ;
	}
	ft_next_token(token_ptr, TOKEN_PIPE);
	ft_add_parse(parse_ptr, node);
}
