/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:20:56 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:02:56 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ft_print_type(int type)
{
	if (type == TOKEN_PIPE)
		ft_printf("TOKEN_PIPE\n");
	else if (type == TOKEN_HEREDOC)
		ft_printf("TOKEN_HEREDOC\n");
	else if (type == TOKEN_APPEND)
		ft_printf("TOKEN_APPEND\n");
	else if (type == TOKEN_INPUT_REDIR)
		ft_printf("TOKEN_INPUT_REDIR\n");
	else if (type == TOKEN_OUTPUT_REDIR)
		ft_printf("TOKEN_OUTPUT_REDIR\n");
	else if (type == TOKEN_ARGUMENT)
		ft_printf("TOKEN_ARGUMENT\n");
	else if (type == TOKEN_FILE)
		ft_printf("TOKEN_FILE\n");
	else if (type == TOKEN_LIMITER)
		ft_printf("TOKEN_LIMITER\n");
	else
		ft_printf("TOKEN_COMMAND\n");
}
