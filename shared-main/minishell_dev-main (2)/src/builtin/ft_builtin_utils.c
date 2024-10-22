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

t_bool	ft_is_builtin(char *value)
{
	if (value == NULL)
		return (false);
	if (ft_check_builtin("export", value)
		|| ft_check_builtin("echo", value)
		|| ft_check_builtin("cd", value)
		|| ft_check_builtin("pwd", value)
		|| ft_check_builtin("unset", value)
		|| ft_check_builtin("env", value)
		|| ft_check_builtin("exit", value))
		return (true);
	else
		return (false);
}

t_bool	ft_check_builtin(char *builtin, char *value)
{
	size_t	len;

	len = ft_strlen(builtin);
	if ((ft_strncmp(builtin, value, len) == 0)
		&& (len == ft_strlen(value)))
		return (true);
	else
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
