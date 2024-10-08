/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:57:22 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/08 15:10:41 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	is_builtin(char	*cmd)
{
	return ((!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
			||(!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
			||(!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
			||(!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
			||(!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
			||(!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4))
}

void	exec_builtin(t_cmd *cmd, char ***env_var, char **export_var)
{
	char	**cmd_line;

	if (!ft_strncmp(cmd->value, "cd", 2))
		cd(cmd);
	if (!ft_strncmp(cmd->value, "pwd", 3))
		pwd();
	if (!ft_strncmp(cmd->value, "env", 3))
		env(*env_var);
	if (!ft_strncmp(cmd->value, "exit", 4))
		;//
	cmd_line = get_cmd_line(cmd->arg->value, cmd->arg->next);
	if (!ft_strncmp(cmd->value, "export", 6))
	{
		if (ft_export(cmd_line, env_var, export_var) == -1)
		{
			free_tab(cmd_line);
			exit(EXIT_FAILURE);
		}
		free_tab(cmd_line);
		exit(EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd, "unset", 5))
		unset(env_var, export_var, cmd_line);
}

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

void	execute(t_cmd *cmd, char ***env_var, char ***export_var)
{
	char	*pathname;
	char	*cmd_name;
	char	**cmd_line;

	if (!cmd)
		return ;
	ft_redir(cmd->redir);
	if (is_builtin(cmd->value) == true)
		exec_builtin(cmd, env_var, export_var);
	if (ft_strchr(cmd->value, '/'))
	{
		pathname = ft_strdup(cmd->value);
		cmd_name = get_cmd_name(cmd->value);
	}
	else
	{
		pathname = get_path(cmd->value, *env_var);
		cmd_name = ft_strdup(cmd->value);
	}
	cmd_line = get_cmd_line(cmd_name, cmd->arg);
	if (execve(pathname, cmd_line, *env_var) == -1)
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
	//init(&cmd, av[1]);
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
