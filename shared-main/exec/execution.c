/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:57:22 by arajaona          #+#    #+#             */
/*   Updated: 2024/09/25 13:35:30 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**get_cmd_line(char *head, t_arg *arg)
{
	t_arg	*temp;
	int		len;
	int		i;
	char	**tab;

	if (arg == NULL)
		return (NULL);
	temp = arg;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	tab = ft_calloc(sizeof(char *), len + 1);
	if (!tab)
		return (NULL);
	i = 0;
	tab[0] = head;
	while (++i < len)
	{
		tab[i] = arg->value;
		arg = arg->next;
	}
	return (tab);
}

char	*extract_path_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (&envp[i][5]);
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*medium;
	char	*sub_path;

	path = ft_split(extract_path_env(envp), ':');
	if (!path)
	{
		error_msg(cmd, "No such file or directory", 0);
		exit (127);
	}
	i = -1;
	while (path[++i])
	{
		medium = ft_strjoin(path[i], "/");
		sub_path = ft_strjoin(medium, cmd);
		if (!access(sub_path, F_OK))
		{
			if (!access(sub_path, X_OK))
				return (free_tab(path), free(medium), sub_path);
			else
			{
				error_msg(cmd, "permission denied", 0);
				free(medium);
				free(sub_path);
				free_tab(path);
				exit (126);
			}
		}
		free (medium);
		free (sub_path);
	}
	free_tab(path);
	error_msg(cmd, "command not found", 1);
	exit(127);
	return (NULL);
}

static char	*get_cmd_name(char *s)
{
	int	start;
	int	end;

	end = 0;
	while (s[end])
		end++;
	start = end;
	while (s[start - 1] != '/')
		start--;
	return (ft_substr(s, start, start - end));
}

void	execute(t_cmd *cmd, char **env)
{
	char	*pathname;
	char	*cmd_name;
	char	**cmd_line;

	ft_redir(cmd->redir);
	if (ft_strchr(cmd->value, '/'))
	{
		pathname = ft_strdup(cmd->value);
		cmd_name = get_cmd_name(cmd->value);
	}
	else
	{
		pathname = get_path(cmd->value, env);
		cmd_name = ft_strdup(cmd->value);
	}
	cmd_line = get_cmd_line(cmd_name, cmd->arg);
	/*if (!cmd_line)
	{
		printf("error in execution (malloc failed)\n");
		free(pathname);
		free(cmd_name);
		exit(EXIT_FAILURE);
	}*/
	if (execve(pathname, cmd_line, env) == -1)
	{
		perror(cmd_name);
		free(pathname);
		free(cmd_line);
		free_tab(cmd_line);
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	t_cmd	cmd;
	int		status;

	if (ac < 2)
		return (0);
	init(&cmd, av[1]);
	pid = fork();
	if (pid == -1)
	{
		printf("fork failed\n");
		exit(1);
	}
	if (!pid)
		execute(&cmd, env);
	else
	{
		wait(&status);
		exit(WEXITSTATUS(status));
	}
}
