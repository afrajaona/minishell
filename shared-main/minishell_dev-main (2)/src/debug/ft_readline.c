/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:21:04 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:00 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

char	*ft_readline(const char *prompt)
{
	size_t	i;
	char	*line;
	t_list	*temp;
	char	*s;

	ft_printf(prompt);
	s = get_next_line(0);
	if (s == NULL)
		return (NULL);
	temp = NULL;
	i = 0;
	while ((s[i] != '\n') && (s[i] != '\0'))
	{
		ft_lstadd_back(&temp, ft_lstnew(&s[i]));
		i++;
	}
	line = ft_to_str(temp);
	free(s);
	ft_clear_temp_list(&temp);
	return (line);
}
