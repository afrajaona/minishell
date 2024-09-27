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

typedef struct s_data
{
	char	*status;
	char	**env;
}				t_data;

void	ft_add_content(t_list **lst, void *content);
char	*ft_lst_to_tab(t_list *lst);
char	*ft_to_str(t_list *lst);
void	ft_clear_tmp(t_list **lst);
void	ft_data_init(t_data *data, int status, char **env);
void    ft_free_data(t_data *data);

#endif
