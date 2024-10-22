/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:21 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:17 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_execve_cmd(t_data *data, t_cmd *cmd);

static void	ft_close_pipe_except(t_parse *node, int pipe1, int pipe2)
{
	int	pipe;

	if (node == NULL)
		return ;
	while (node != NULL)
	{
		if ((node->type == TOKEN_PIPE) && (node->data.pipe != NULL))
		{
			pipe = node->data.pipe->pipeid;
			if ((pipe != pipe1) && (pipe != pipe2))
			{
				close(node->data.pipe->pipefd[1]);
				close(node->data.pipe->pipefd[0]);
			}
		}
		node = node->next;
	}
}

static void	ft_close_unused_pipe(t_data *data, t_parse *node)
{
	int	pipe1;
	int	pipe2;

	if ((data == NULL) || (node == NULL) || (node->type != TOKEN_COMMAND)
		|| ((node->prev != NULL) && (node->prev->type != TOKEN_PIPE))
		|| ((node->next != NULL) && (node->next->type != TOKEN_PIPE))
		|| data->cmds == NULL)
		return ;
	pipe1 = -1;
	pipe2 = -1;
	if ((node->prev != NULL) && (node->prev->type == TOKEN_PIPE)
		&& (node->prev->data.pipe != NULL))
	{
		pipe1 = node->prev->data.pipe->pipeid;
		close(node->prev->data.pipe->pipefd[1]);
	}
	if ((node->next != NULL) && (node->next->type == TOKEN_PIPE)
		&& (node->next->data.pipe != NULL))
	{
		pipe2 = node->next->data.pipe->pipeid;
		close(node->next->data.pipe->pipefd[0]);
	}
	ft_close_pipe_except(data->cmds, pipe1, pipe2);
}

int	ft_input_process_set(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

void	ft_check_redir(t_redir *redir)
{
	t_list	*file;
	char	*filename;

	if (redir == NULL)
		return ;
	file = redir->value.input_redir.expand;
	if (ft_lstsize(file) != 1)
	{
		filename = redir->value.input_redir.filename;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		exit(1);
	}
}

int	ft_output_process_set(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

static void	ft_set_process_io(t_data *data, t_parse *node)
{
	if ((data == NULL) || (ft_check_cmd(node) == false))
		return ;
	if ((node->prev != NULL) && (node->prev->type == TOKEN_PIPE)
		&& (node->prev->data.pipe != NULL))
		ft_input_process_set(node->prev->data.pipe->pipefd[0]);
	if ((node->next != NULL) && (node->next->type == TOKEN_PIPE)
		&& (node->next->data.pipe != NULL))
		ft_output_process_set(node->next->data.pipe->pipefd[1]);
}

int	ft_input_redir(t_data *data, t_redir *redir)
{
	int	fd;
	char	*pathname;
	t_list	*input_redir;

	if ((data == NULL) || (redir == NULL))
		return (-1);
	ft_check_redir(redir);
	input_redir = redir->value.input_redir.expand;
	pathname = (char *) input_redir->content;
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		exit(1);
	ft_input_process_set(fd);
	close(fd);
	return (0);
}

int	ft_output_redir(t_data *data, t_redir *redir)
{
	int	fd;
	char	*pathname;
	t_list	*output_redir;

	if ((data == NULL) || (redir == NULL))
		return (-1);
	ft_check_redir(redir);
	output_redir = redir->value.output_redir.expand;
	pathname = (char *) output_redir->content;
	fd = open (pathname, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		exit(1);
	ft_output_process_set(fd);
	close(fd);
	return (0);
}

int	ft_append(t_data *data, t_redir *redir)
{
	int	fd;
	char	*pathname;
	t_list	*append;

	if ((data == NULL) || (redir == NULL))
		return (-1);
	ft_check_redir(redir);
	append = redir->value.append.expand;
	pathname = (char *) append->content;
	fd = open (pathname, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		exit(1);
	ft_output_process_set(fd);
	close(fd);
	return (0);
}

void	ft_exec_input_redir(t_data *data, t_redir *redir)
{
	int	pipefd;

	if ((data == NULL) || (redir == NULL))
		return ;
	if (redir->type == TOKEN_INPUT_REDIR)
		ft_input_redir(data, redir);
	if ((redir->type == TOKEN_HEREDOC) && redir->value.heredoc.is_exec)
	{
		pipefd = redir->value.heredoc.pipefd[0];
		ft_input_process_set(pipefd);
	}
}

void	ft_exec_output_redir(t_data *data, t_redir *redir)
{
	if ((data == NULL) || (redir == NULL))
		return ;
	if (redir->type == TOKEN_OUTPUT_REDIR)
		ft_output_redir(data, redir);
	if (redir->type == TOKEN_APPEND)
		ft_append(data, redir);
}

int	ft_exec_redir(t_data *data, t_parse *node)
{
	t_type	type;
	t_redir	*redir;

	if ((data == NULL) || (ft_check_cmd(node) == false)
		|| (node->data.cmd->redir == NULL))
		return (-1);
	redir = node->data.cmd->redir;
	while (redir != NULL)
	{
		type = redir->type;
		if ((type == TOKEN_INPUT_REDIR) || (type == TOKEN_HEREDOC))
			ft_exec_input_redir(data, redir);
		else if ((type == TOKEN_OUTPUT_REDIR) || (type == TOKEN_APPEND))
			ft_exec_output_redir(data, redir);
		else
			return (-1);
		redir = redir->next;
	}
	return (0);
}

void	ft_exec_cmd(t_data *data, t_parse *node)
{
	t_cmd	*cmd;

	if ((data == NULL) || (ft_check_cmd(node) == false))
		return ;
	cmd = node->data.cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
		data->exit.value = 1;
	if (cmd->pid == 0)
	{
		ft_close_unused_pipe(data, node);
		ft_set_process_io(data, node);
		ft_exec_redir(data, node);
		if (ft_is_builtin(cmd->value))
			exit(ft_exec_builtin(data, cmd, 0));
		else
			ft_execve_cmd(data, cmd);
		exit(42);
	}
}

static void	ft_execve_cmd(t_data *data, t_cmd *cmd)
{
	t_exec	exec;

	if ((data == NULL) || (cmd == NULL) || (cmd->value == NULL))
		return ;
	ft_init_exec_value(&exec);
	ft_get_exec_value(data, &exec, cmd);
	ft_set_default_signal();
	execve(exec.value, exec.argv, data->env);
	if (errno == EACCES)
		exit(1);
	else
		exit(1);
}
