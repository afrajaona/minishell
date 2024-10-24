/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:54 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/24 13:33:46 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *target, char **envp)
{
	int	i;
	int	size;

	size = ft_strlen(target);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], target, size))
			return (&envp[i][size + 1]);
	}
	return (NULL);
}
