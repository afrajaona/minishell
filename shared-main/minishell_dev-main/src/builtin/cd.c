/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:57:23 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/15 15:14:46 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*tmp_cmd(char *object, char *value)
{
	t_cmd	*ret;
	
	ret = ft_calloc(sizeof(t_cmd), 1);
	ret->pid = 0;
	ret->value = NULL;
	ret->redir = NULL;
	ret->arg = ft_calloc(sizeof(t_arg), 1);
	ret->arg->value =  ft_strjoin(object, value);
	ret->arg->next = NULL;
	return (ret);
}

static int	update_pwd(t_data *data)
{
	char    location[1024];
	t_cmd	*cmd;

	if (ft_getenv("PWD", data->env))
	{
		if (getcwd(location, sizeof(location)))
		{
			cmd = tmp_cmd("PWD=", location);
			ft_export(data, cmd);
			ft_clear_cmd(cmd);
		}
		else
			return (ft_putendl_fd("minishell: cd: PWD not updated", 2), 0);
	}
	return (1);
}

static int	update_oldpwd(t_data *data)
{
	char	location[1024];
	t_cmd	*cmd;

	if (ft_getenv("OLDPWD", data->env))
	{
		if (getcwd(location, sizeof(location)))
		{
			cmd = tmp_cmd("OLDPWD=", location);
			ft_export(data, cmd);
			ft_clear_cmd(cmd);
		}
		else
			return (ft_putendl_fd("minishell: cd: OLDPWD not updated", 2), 0);
	}
	return (1);
}

static int	go_to_home(t_data *data)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME", data->env);
	if (!home_dir)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home_dir))
	{
		perror("minishell: cd: ");
		return (1);
	}
	return (0);
}

int	cd(t_data *data, t_cmd *cmd)
{
	t_arg	*tmp;
	int		i;

	tmp = cmd->arg;
	if (!tmp)
		return (go_to_home(data));
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (i > 1)
		return(ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!update_oldpwd(data))
		return (1);
	if (chdir(cmd->arg->value))
		return (error_msg("cd", strerror(errno), 0), 1);
	if (!update_pwd(data))
		return (1);
	return (0);
}
