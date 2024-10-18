/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:19:36 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**get_cmd_line(char *head, t_arg *arg)
{
	t_arg	*temp;
	int		len;
	int		i;
	char	**tab;

	temp = arg;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	tab = ft_calloc(sizeof(char *), len + 2);
	if (!tab)
	{
		ft_putendl_fd("failed to allocate memory for cmd_line", 2);
		return (NULL);
	}
	i = 0;
	temp = arg;
	tab[0] = head;
	while (++i < len + 1)
	{
		tab[i] = temp->value;
		temp = temp->next;
	}
	return (tab);
}

t_bool	ft_is_builtin(t_data *data, t_cmd *cmd)
{
	char	*next;
	
	if (cmd->value == NULL)
		return (false);
	if (cmd->arg)
		next = cmd->arg->value;
	else
		next = NULL;
	if (ft_check_builtin("export", cmd->value, next, data)
		|| ft_check_builtin("echo", cmd->value, next, data)
		|| ft_check_builtin("cd", cmd->value, next, data)
		|| ft_check_builtin("pwd", cmd->value, next, data)
		|| ft_check_builtin("unset", cmd->value, next, data)
		|| ft_check_builtin("env", cmd->value, next, data)
		|| ft_check_builtin("exit", cmd->value, next, data))
		return (true);
	else
		return (false);
}

t_bool	ft_check_builtin(char *builtin, char *value, char *next, t_data *data)
{
	size_t	len;
	(void)data;//
	len = ft_strlen(builtin);
	if ((ft_strncmp(builtin, value, len) == 0)
		&& (len == ft_strlen(value)))
	{
		if (!ft_strncmp(builtin, "echo", len)
			&& (!(!ft_strchr(next, '-')
			|| !ft_strncmp(next, "-n", 2)))) // plus checking if PATH exists AND is correctly set, hence data
			return (false);
		return (true);
	}
	return (false);
}

void	error_msg(char *target, char *message, int path_on)
{
	int	tmp_fd;

	tmp_fd = dup(1);
	dup2(2, 1);
	if (path_on)
		printf("%s: %s\n", target, message);
	else
		printf("minishell: %s: %s\n", target, message);
	dup2(tmp_fd, 1);
}
