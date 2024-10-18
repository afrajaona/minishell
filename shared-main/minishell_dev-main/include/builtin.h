/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:18:11 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 00:59:47 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lexer.h"
# include "exec.h"
# include "utils.h"

char	*ft_getenv(char *target, char **envp);
char	**get_cmd_line(char *head, t_arg *arg);
int	cd(t_data *data, t_cmd *cmd);
int	ft_display_tab(char *envp[], int put_new_line, int put_space, int put_endl);
int	ft_echo(t_cmd *cmd);
int	ft_exec_builtin(t_data *data, t_cmd *cmd);
int	ft_exit(t_data *data, t_cmd *cmd);
int	ft_export(t_data *data, t_cmd *cmd);
int	ft_insert_var(char **input, char ***envp);
int	handle_export_error(char *input);
int	pwd(void);
int	unset(t_data *data, t_cmd *cmd);
size_t	ft_atoll(const char *nptr);
t_bool	ft_is_builtin(t_data *data, t_cmd *cmd);
t_bool	ft_check_builtin(char *builtin, char *value, char *next, t_data *data);
void    error_msg(char *target, char *message, int path_on);
void	sort_print(char **tab);

#endif
