/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:21:52 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/15 15:41:33 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_display_tab(char *envp[], int put_new_line, int put_space, int put_endl)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		ft_putstr_fd(envp[i], 1);
		if (put_new_line)
			write(1, "\n", 1);
		if (put_space)
			write(1, " ", 1);
	}
	if (put_endl)
		write(1, "\n", 1);
	return (0);
}
