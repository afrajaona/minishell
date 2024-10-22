/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:05:27 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:03:30 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#define PATH "."

static char	*ft_get_path_value(char **env);
static void	ft_add_suffix(char **strs, char *suffix);
static int	ft_find_file(char **paths, char *filename);

char	*ft_find_cmd(char *name, char **env)
{
	int		res;
	char	*path;
	char	**paths;
	char	*exec;

	path = ft_get_path_value(env);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	ft_add_suffix(paths, "/");
	res = ft_find_file(paths, name);
	if (res == -1)
		exec = NULL;
	else
		exec = ft_strdup(paths[res]);
	//ft_free_strs(paths);
	return (exec);
}

static char	*ft_get_path_value(char **env)
{
	size_t	i;
	size_t	j;
	char	*var_name;

	var_name = "PATH";
	i = 0;
	if (*env == NULL)
		return (PATH);
	while (env[i] != NULL)
	{
		if (env[i][0] == var_name[0])
		{
			j = 0;
			while ((var_name[j] == env[i][j]) && (var_name[j] != '\0'))
				j++;
			if (var_name[j] == '\0')
				return (env[i] + ft_strlen(var_name) + 1);
		}
		i++;
	}
	return (PATH);
}

static void	ft_add_suffix(char **strs, char *suffix)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (strs[i] != NULL)
	{
		tmp = strs[i];
		strs[i] = ft_strjoin(strs[i], suffix);
		if (strs[i] == NULL)
			strs[i] = tmp;
		else
			free(tmp);
		i++;
	}
}

static int	ft_find_file(char **paths, char *filename)
{
	size_t	i;

	ft_add_suffix(paths, filename);
	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
			return (i);
		i++;
	}
	i--;
	if (ft_strncmp(paths[i], PATH, ft_strlen(PATH)) == 0)
		exit(127);
	return (-1);
}
