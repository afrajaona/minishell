/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:29 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:22 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_exec_parse(t_data *data, t_parse *parse);
static void	ft_exec_cmds(t_data *data, t_parse *parse);

void	ft_exec_line(t_data *data, char *line, char **history_ptr)
{
	if (ft_parse(data, &data->cmds, line, history_ptr) != 0)
		return ;
	if (ft_exec_parse(data, data->cmds) != 0)
		return ;
	// todo: free_parse
}

void	ft_close_all_pipes(t_parse *parse)
{
	if (parse == NULL)
		return ;
	while (parse != NULL)
	{
		if ((parse->type == TOKEN_PIPE) && (parse->data.pipe != NULL))
		{
			close(parse->data.pipe->pipefd[1]);
			close(parse->data.pipe->pipefd[0]);
		}
		parse = parse->next;
	}
}

void	ft_exec_parse_cmds(t_data *data, t_parse *parse)
{
	if ((data == NULL) || (parse == NULL)
		|| (ft_check_parse(parse) == false))
		return ;
	while (parse != NULL)
	{
		if (parse->type == TOKEN_PIPE)
			parse = parse->next;
		else
		{
			ft_exec_cmds(data, parse);
			parse = parse->next;
		}
	}
}

static int	ft_exec_parse(t_data *data, t_parse *parse)
{
	t_parse	*cmds;

	if ((data == NULL) || (parse == NULL)
		|| (ft_check_parse(parse) == false))
		return (-1);
	cmds = parse;
	signal(SIGINT, SIG_IGN);
	ft_create_pipes(parse);
	ft_exec_parse_cmds(data, parse);
	ft_close_all_pipes(cmds);
	ft_wait_cmds(data, cmds);
	signal(SIGINT, ft_input_handle);
	return (0);
}

static void	ft_exec_cmds(t_data *data, t_parse *parse)
{
	t_cmd	*cmd;

	if ((data == NULL) || (ft_check_cmd(parse) == false))
		return ;
	cmd = parse->data.cmd;
	if (ft_is_builtin(cmd->value) && (parse->prev == NULL)
		&& (parse->next == NULL))
		data->exit.value = ft_exec_builtin(data, parse->data.cmd, 1);
	else
		ft_exec_cmd(data, parse);
}
