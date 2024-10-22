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

static void	ft_shell_prompt(t_data *data);

int	g_sigint = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_set_signal();
	ft_init_data(&data, ac, av, env);
	ft_shell_prompt(&data);
	return (0);
}

void	ft_update_status(t_data *data)
{
	if (data == NULL)
		return ;
	if (g_sigint == 1)
	{
		data->exit.value = 130;
		ft_redir_to_tty(data->tty, STDIN_FILENO);
	}
}

void	ft_reset_sig_flag(void)
{
	g_sigint = 0;
}

void	ft_add_history(char *history)
{
	if ((history == NULL) || ft_isspace(history[0]))
		return ;
	add_history(history);
}

void	ft_exit_prompt(void)
{
	ft_putendl_fd("exit", 2);
	exit(0);
}

static void	ft_shell_prompt(t_data *data)
{
	char	*line;
	char	*history;

	if ((data == NULL) || (data->tty == NULL))
		return ;
	history = NULL;
	while (1)
	{
		line = readline(PROMPT);
		ft_update_status(data);
		if ((g_sigint == 0) && (line == NULL))
			ft_exit_prompt();
		if (ft_isempty(line))
			free(line);
		else
		{
			ft_exec_line(data, line, &history);
			ft_add_history(history);
		}
		ft_reset_sig_flag();
	}
	rl_clear_history();
}
