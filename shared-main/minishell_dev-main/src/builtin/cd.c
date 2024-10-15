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

static int	update_pwd(t_data *data)
{
	char    location[1024];
    char    **tmp;

    if (ft_getenv("PWD", data->env))
    {
        if (getcwd(location, sizeof(location)))
        {
            tmp = ft_calloc(sizeof(char *), 2);
            tmp[0] = ft_strjoin("PWD=", location);
            ft_export(tmp, &data->env, &data->ex_var);
            free_tab(tmp);
        }
        else
            return (ft_putendl_fd("minishell: cd: PWD not updated", 2), 0);
    }
    return (1);
}

static int	update_oldpwd(t_data *data)
{
	char	location[1024];
	char	**tmp;

	if (ft_getenv("OLDPWD", data->env))
	{
		if (getcwd(location, sizeof(location)))
		{
			tmp = ft_calloc(sizeof(char *), 2);
			tmp[0] = ft_strjoin("OLDPWD=", location);
			ft_export(tmp, &data->env, &data->ex_var);
			free_tab(tmp);
		}
		else
			return (ft_putendl_fd("minishell: cd: OLDPWD not updated", 2), 0);
	}
	return (1);
}

static int	got_to_home(t_data *data)
{
	char	home_dir;

	home_dir = ft_getenv("HOME", data->env);
	if (!home_dir)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home_dir))
	{
		perror("minishell: cd: ")
		return (1);
	}
	return (0);
}

int	cd(t_data *data, t_cmd *cmd)
{
	t_arg	*tmp;
	int		i;
	int		tmp_fd;

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
