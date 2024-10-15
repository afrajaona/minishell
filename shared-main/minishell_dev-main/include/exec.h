/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:27:58 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:00:00 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parse.h"
# include "builtin.h"
# include "utils.h"

void	ft_exec_line(t_data *data, char *line);
void	ft_create_pipes(t_parse *parse);
char	*ft_find_cmd(char *name, char **env);
void	ft_find_exec(t_data *data, char **exec_ptr, t_cmd *cmd);
t_bool	ft_check_cmd(t_parse *node);
void	ft_init_exec_value(t_exec *exec);
void	ft_get_exec_value(t_data *data, t_exec *exec, t_cmd *cmd);
void	ft_exec_cmd(t_data *data, t_parse *parse);
void	ft_wait_cmds(t_data *data, t_parse *parse);

#endif
