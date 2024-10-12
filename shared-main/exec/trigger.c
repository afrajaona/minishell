/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:47:00 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/12 15:47:21 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wait(int pid[], int nb, int *exit_status)
{
	int	status;
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			printf("wait failed\n");
	}
	*exit_status = WEXITSTATUS(status);
}

int	count_cmd(t_parse *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line->type == TOKEN_PIPE)
		{
			line = line->next;
			continue;
		}
		i++;
		line = line->next;
	}
	return (i);
}

int	**init_pipes(int nb)
{
	int	**root;
	int	i;

	root = malloc(sizeof(int *) * nb);
	i = -1;
	while (++i < nb)
		root[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < nb)
	{
		if (pipe(root[i]) == -1)
			perror("pipe");
	}
	return (root);
}

void	exec_line(t_parse *line, int **pipelines, int branch_nb, t_data *data)
{
	int	pid[branch_nb];
	int	nb;

	nb = 0;
	while (nb < branch_nb)
	{
		if (!line)
			break;
		if (line->type == TOKEN_PIPE)
		{
			line = line->next;
			continue;
		}
		nb++;
		if (line->prev)
			dup2(pipelines[nb - 1][0], 0);
		if (line->next)
			dup2(pipelines[nb][1], 1);
		pid[nb] = fork();
		if (pid[nb] == -1)
		{
			printf("fork failed\n");
			exit(EXIT_FAILURE);
		}
		if (!pid[nb])
			execute(line->data.cmd, data, 0);
		line = line->next;
	}
	ft_wait(pid, branch_nb, &data->status);
}

void	launch(t_parse *line, t_data *data)
{
	int	branch_nb;
	int	pid;
	int	status;
	int	**pipelines;

	branch_nb = count_cmd(line);
	if (branch_nb == 1)
	{
		if (is_builtin(line->data.cmd->value) == true)
			exec_builtin(line->data.cmd, data, 1);
		else
		{
			pid = fork();
			if (pid == -1)
			{
				ft_putstr_fd("minishell: launch failure\n", 2);
				return ;
			}
			if (!pid)
				execute(line->data.cmd, data, 0);
			else
				waitpid(pid, &status, 0);
			data->status = WEXITSTATUS(status);
		}
		return ;
	}
	pipelines = init_pipes(branch_nb - 1);
	exec_line(line, pipelines, branch_nb, data);
}
