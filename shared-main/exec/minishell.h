/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:47:03 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/12 14:05:23 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "utils.h"
# include "parse.h"
# include "token.h"

# define EXIT_SHELL 42

extern volatile sig_atomic_t    g_received_sigint;

char    **ft_tab_dup(char **tab);
int		ft_export(char	**input, char ***env_var, char ***export_var);
size_t	ft_atoll(const char *nptr);
t_bool	is_builtin(char	*cmd);
void	cd(t_cmd *cmd, t_data *data);
void	env(char *envp[]);
void	execute(t_cmd *cmd, t_data *data, int flag);
void	free_tab(char **s);
void	ft_exit(t_data *data, t_cmd *cmd);
char	**get_cmd_line(char *head, t_arg *arg);
void	handle_signals(void);
void	launch(t_parse *line, t_data *data);
void	pwd(void);
void	sort_print(char **tab);
void	update_data(t_data *data);
void    unset(char ***envp, char ***export_var, char **input);

#endif
