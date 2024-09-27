/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:56:45 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:31:47 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define TOKEN_COMMAND			1
# define TOKEN_ARGUMENT			2
# define TOKEN_PIPE				3
# define TOKEN_HEREDOC			4
# define TOKEN_APPEND			5
# define TOKEN_INPUT_REDIR		6
# define TOKEN_OUTPUT_REDIR		7
# define TOKEN_FILE				8
# define TOKEN_LIMITER			9
# define TOKEN_GENERAL			10
# define TOKEN_VARIABLE			11

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'

typedef int	t_type;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_expand
{
	t_type			type;
	char			*value;
	struct s_expand	*next;
}				t_expand;

typedef struct s_token
{
	t_type			type;
	char			*value;
	t_expand		*expand;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

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
