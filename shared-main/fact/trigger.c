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

void	close_unused_pipes(int	**pipelines, int index, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		if (i != index - 1 && i != index)
		{
			close(pipelines[i][0]);
			close(pipelines[i][1]);
		}
		i++;
	}
}

void	ft_wait(int pid[], int nb, int *exit_status)
{
	int	status;
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			printf("wait failed at pipe number %i\n", i);
	}
	*exit_status = WEXITSTATUS(status);
}

int	count_cmd(t_parse *line)
{
	int	i;
	t_parse	*tmp;

	i = 0;
	tmp = line;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			tmp = tmp->next;
			continue;
		}
		i++;
		tmp = tmp->next;
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
	
	nb = -1;
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
		pid[nb] = fork();
		if (pid[nb] == -1)
		{
			ft_putstr_fd("fork failed\n", 2);
			exit(EXIT_FAILURE);
		}
		if (!pid[nb])
		{
			close_unused_pipes(pipelines, nb, branch_nb - 1);
			if (line->prev && pipelines[nb - 1])
			{
				close(pipelines[nb - 1][1]);
				if (dup2(pipelines[nb - 1][0], 0) == -1)
					ft_putendl_fd("stdin has not been redirected!", 2);
				close(pipelines[nb - 1][0]);
			}
			if (line->next && pipelines[nb])
			{
				close(pipelines[nb][0]);
				if (dup2(pipelines[nb][1], 1) == -1)
					ft_putendl_fd("stdout has not been redirected!", 2);
				close(pipelines[nb][1]);
			}
			execute(line->data.cmd, data, 0);
		}
		line = line->next;
	}
	for (int i = 0; i < branch_nb - 1; i++)
	{
		if (pipelines[i])
		{
			close(pipelines[i][0]);
			close(pipelines[i][1]);
		}
	}
	ft_wait(pid, branch_nb, &data->status);
}

void	launch(t_parse *line, t_data *data)
{
	int	branch_nb;
	int	pid;
	int	status;
	int	**pipelines;

	handle_signals();
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
