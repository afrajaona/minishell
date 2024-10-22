/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:52:04 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:06:16 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	ft_flag_init(t_flag *flag)
{
	flag->redir = false;
	flag->cmd = false;
	flag->heredoc = false;
}

void	ft_set_flag(t_flag *flag, t_bool redir, t_bool cmd, t_bool heredoc)
{
	flag->redir = redir;
	flag->cmd = cmd;
	flag->heredoc = heredoc;
}
