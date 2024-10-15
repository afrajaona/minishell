/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:55:46 by arajaona          #+#    #+#             */
/*   Updated: 2024/10/15 15:58:38 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export_error(char **input, int index)
{
	if (!ft_isalpha((*input)[0]))
	{
		printf("minishell: export : `%s': not a valid identifier\n", *input);
		return (-1);
	}
	if (input[++index])
		return (handle_export_error(&input[index]));
	return (0);
}

static int	create_env_var(char ***envp, char *input)
{
	char	**new_envp;
	int		env_count;
	int		i;

	env_count = 0;
	while ((*envp)[env_count])
		env_count++;
	new_envp = ft_calloc(env_count + 2, sizeof(char *));
	if (!new_envp)
		return (-1);
	i = -1;
	while ((*envp)[++i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if(!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (-1);
		}
	}
	new_envp[i] = ft_strdup(input);
	free_tab(*envp);
	*envp = new_envp;
	return (0);
}

static int	overwrite_env_var(char **environ, char *input)
{
	int	i;

	i = 0;
	while (input[i] != '=')
		i++;
	while (*environ)
	{
		if (!ft_strncmp(input, *environ, i) && ((*environ)[i] == '=' || !(*environ)[i]))		{
			free(*environ);
			*environ = ft_strdup(input);
			if (!*environ)
				return (-1);
		}
		environ++;
	}
	return (0);
}

static int	var_exists(char *name, char **environ)
{
	size_t	len_name;

	len_name = ft_strlen(name);
	while (*environ)
	{
		if (!ft_strncmp(name, *environ, len_name) &&
		((*environ)[len_name] == '=' || !(*environ)[len_name]))
			return (1);
		environ++;
	}
	return (0);
}

int	ft_insert_var(char **input, char ***envp)
{
	int	exit_status;
	char	**cmd_line;
	char	**environ;
	
	cmd_line = ft_split(*input, '=');
	environ = *envp;
	if (var_exists(cmd_line[0], environ))
	{
		free_tab(cmd_line);
		exit_status = overwrite_env_var(environ, *input);
	}
	else
	{
		free_tab(cmd_line);
		exit_status = create_env_var(envp, *input);
	}
	return (exit_status);
}
