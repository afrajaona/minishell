/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:22:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_set_sigflag(t_sigflag *sigflag)
{
	if (sigflag == NULL)
		return ;
	sigflag->sigquit = 0;
	sigflag->sigint = 0;
}

void	ft_get_wstatus(t_data *data, pid_t pid, t_sigflag *sigflag)
{
	pid_t	wpid;
	int		wstatus;

	if ((data == NULL) || (sigflag == NULL))
		return ;
	wstatus = 0;
	wpid = waitpid(pid, &wstatus, 0);
	if (wpid == -1)
		data->exit.value = 1;
	if (WIFEXITED(wstatus))
	{
		sigflag->sigquit = 0;
		data->exit.value = WEXITSTATUS(wstatus);
	}
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == 3)
			sigflag->sigquit = 1;
		else if (WTERMSIG(wstatus) == 2)
			sigflag->sigint = 1;
		data->exit.value = 128 + WTERMSIG(wstatus);
	}
}

void	ft_wait_cmds(t_data *data, t_parse *parse)
{
	t_sigflag	sigflag;

	ft_set_sigflag(&sigflag);
	while (parse != NULL)
	{
		if ((parse->type != TOKEN_COMMAND) || (parse->data.cmd == NULL)
			|| (parse->data.cmd->pid == -1))
			parse = parse->next;
		else
		{
			ft_get_wstatus(data, parse->data.cmd->pid, &sigflag);
			parse = parse->next;
		}
	}
	if (sigflag.sigquit != 0)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (sigflag.sigint != 0)
		ft_putendl_fd("", 2);
}
