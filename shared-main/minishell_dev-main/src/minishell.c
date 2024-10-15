/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:27:29 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:53 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	ft_set_signal();
	ft_init_data(&data, argc, argv, env);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (ft_isempty(line))
			free(line);
		else
		{
			add_history(line);
			ft_exec_line(&data, line);
		}
	}
	rl_clear_history();
	exit(0);
}
