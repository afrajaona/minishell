/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:01:10 by arajaona          #+#    #+#             */
/*   Updated: 2024/07/10 14:04:48 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*location;

	location = getcwd(NULL, 0);
	if (location)
	{
		printf("%s\n", location);
		free(location);
		return (0);
	}
	return (1);
}
