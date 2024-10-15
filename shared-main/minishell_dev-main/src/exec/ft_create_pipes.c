/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:15 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:05 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_create_pipes(t_parse *parse)
{
	int		pipe_id;
	t_pipe	*pipe_ptr;

	if (parse == NULL)
		return ;
	pipe_id = 0;
	while (parse != NULL)
	{
		if ((parse->type == TOKEN_PIPE)
			&& (parse->data.pipe != NULL))
		{
			pipe_ptr = parse->data.pipe;
			if (pipe(pipe_ptr->pipefd) == -1)
				exit(1);
			pipe_ptr->pipe_id = pipe_id;
			pipe_id++;
		}
		parse = parse->next;
	}
}
