/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 01:36:35 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/15 01:59:29 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void ft_input_handle(int signal)
{
	int	pipefd[2];

    if (signal == SIGINT)
    {
    	g_sigint = 1;
    	if (pipe(pipefd) == -1)
        {
    	    perror("pipe");
            return ;
        }
    	dup2(pipefd[0], STDIN_FILENO);
    	write(pipefd[1], "\n", 1);
    	close(pipefd[0]);
    	close(pipefd[1]);
    }
}

void	ft_sigint_handle(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void    ft_set_default_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	ft_set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_handle);
}