/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:09:19 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/18 16:00:01 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_arg(t_arg **arg)
{
	t_arg	*next;
	
	while(*arg)
	{
		next = (*arg)->next;
		free((*arg)->value);
		free(*arg);
		*arg = next;
	}
	*arg = NULL;
}

void	ft_clear_redir_input(t_redir **redir)
{
	if ((*redir)->type == TOKEN_INPUT_REDIR)
	{
		free((*redir)->value.input_redir.filename);
		ft_clear_list(&(*redir)->value.input_redir.expand);
	}
	else if ((*redir)->type == TOKEN_OUTPUT_REDIR)
	{
		free((*redir)->value.output_redir.filename);
        	ft_clear_list(&(*redir)->value.output_redir.expand);
	}
	else if ((*redir)->type == TOKEN_APPEND)
	{
		free((*redir)->value.append.filename);
        	ft_clear_list(&(*redir)->value.append.expand);
	}
	else
	{
		free((*redir)->value.heredoc.limiter);
		free((*redir)->value.heredoc.expand);
		//close(*redir.value.heredoc.pipefd[0]);
		//close(*redir.value.heredoc.pipefd[1]);
	}
}

void	ft_clear_redir(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		ft_clear_redir_input(redir);
		free(*redir);
		*redir = tmp;
	}
	*redir = NULL;
}

void	ft_clear_cmd(t_cmd *cmd)
{
	free(cmd->value);
	ft_clear_redir(&cmd->redir);
	ft_clear_arg(&cmd->arg);
	free(cmd);
}
