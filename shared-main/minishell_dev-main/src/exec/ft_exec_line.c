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

void	ft_exec_line(t_data *data, char *line)
{
	t_parse	*cmds;

	ft_parse(data, &cmds, line);
	ft_exec_parse(data, cmds);
	// todo: free_parse
}

static int	ft_exec_parse(t_data *data, t_parse *parse)
{
	t_parse	*cmds;

	if ((data == NULL) || (parse == NULL)
		|| (ft_check_parse(parse) == false))
		return (-1);
	signal(SIGINT, SIG_IGN);
	cmds = parse;
	//ft_create_pipes(parse);
	while (parse != NULL)
	{
		if (parse->type == TOKEN_PIPE)
			parse = parse->next;
		else
		{
			if (ft_is_builtin(data, parse->data.cmd))
				exit(ft_exec_builtin(data, parse->data.cmd));
			else
				ft_exec_cmds(data, parse);
			parse = parse->next;
		}
	}
	ft_wait_cmds(data, cmds);
	signal(SIGINT, ft_sigint_handle);
	return (0);
}

static void	ft_exec_cmds(t_data *data, t_parse *parse)
{
	t_cmd	*cmd;

	if ((data == NULL) || (ft_check_cmd(parse) == false))
		return ;
	cmd = parse->data.cmd;
	if (ft_is_builtin(data, parse->data.cmd) && (parse->prev == NULL)
		&& (parse->next == NULL))
		data->exit.value = ft_exec_builtin(data, parse->data.cmd);
	else
		ft_exec_cmd(data, parse);
}
