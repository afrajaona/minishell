/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:20:14 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:34:43 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# define PROMPT			"minishell> "
# define TESTPROMPT		"tests> "

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_INPUT_REDIR,
	TOKEN_OUTPUT_REDIR,
	TOKEN_FILE,
	TOKEN_LIMITER,
	TOKEN_STR,
	TOKEN_VAR
}			t_token_type;

typedef struct s_data
{
	char	*exit;
	char	**env;
}				t_data;

void	ft_init_data(t_data *data, int exit_status, char **env);
void	ft_free_data(t_data *data);

#endif
