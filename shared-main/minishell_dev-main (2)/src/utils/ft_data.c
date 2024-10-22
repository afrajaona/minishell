/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:01:22 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:29 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	char	**env;

	(void) argc;
	(void) argv;
	env = ft_tab_dup(envp);
	data->tty = ttyname(STDIN_FILENO);
	if (data->tty == NULL)
	{
		perror("ttyname");
		exit(1);
    	}
	data->env = env;
	data->ex_var = ft_tab_dup(envp);
	data->exit.value = 0;
	data->exit.conv_addr = NULL;
	data->cmds = NULL;
}

void	ft_free_data(t_data *data)
{
	ft_clear_list(&data->exit.conv_addr);
	ft_clear_tab(data->env);
	ft_clear_tab(data->ex_var);
}
