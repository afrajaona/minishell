/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:23:30 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:34 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	ft_check_pipe_node(t_parse *parse)
{
	if ((parse == NULL) || (parse->type != TOKEN_PIPE) 
		|| (parse->prev == NULL) || (parse->next == NULL))
		return (false);
	if ((parse->prev->type == TOKEN_COMMAND)
		&& (parse->next->type == TOKEN_COMMAND))
		return (true);
	else
		return (false);
}


t_bool	ft_check_cmd_node(t_parse *parse)
{
	if ((parse == NULL) || (parse->type != TOKEN_COMMAND))
		return (false);
	if (((parse->prev == NULL) || (parse->prev->type == TOKEN_PIPE))
		&& ((parse->next == NULL) || (parse->next->type == TOKEN_PIPE)))
		return (true);
	else
		return (false);
}

t_bool	ft_check_parse(t_parse *parse)
{
	t_bool	res;

	if ((parse == NULL) || (parse->prev != NULL)
		|| (parse->type != TOKEN_COMMAND))
		return (false);
	while (parse != NULL)
	{
		if (parse->type == TOKEN_PIPE)
			res = ft_check_pipe_node(parse);
		else if (parse->type == TOKEN_COMMAND)
			res = ft_check_cmd_node(parse);
		else
			res = false;
		if (res == false)
			return (false);
		parse = parse->next;
	}
	return (true);
}
