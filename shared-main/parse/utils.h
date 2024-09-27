/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:56:45 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/30 16:56:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'

typedef int	t_type;

typedef enum e_bool
{
	false,
	true
}			t_bool;

void	ft_add_str_in_delim(t_list **temp, char *s, char delim, size_t *index);
void	ft_add_content(t_list **lst, void *content);
t_bool	ft_s_compare(char *s1, char *s2);

#endif
