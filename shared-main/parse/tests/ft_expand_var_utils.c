/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:50:10 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/21 19:33:09 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

t_bool	ft_is_var(char *s, size_t pos)
{
	if ((s == NULL) || ((ssize_t) pos < 0))
		return (false);
	if ((s[pos] == '$') && (ft_isalpha(s[pos + 1])
			|| (s[pos + 1] == '_') || (s[pos + 1] == '?')))
		return (true);
	else
		return (false);
}

char	*ft_get_varvalue(char *var_name, size_t var_len, char **env)
{
	size_t	i;

	i = 0;
	if (*env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (var_len == ft_envvar_len(env[i])
			&& (ft_strncmp(env[i], var_name, var_len) == 0))
				return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

size_t	ft_envvar_len(char *envvar_name)
{
	size_t	len;

	len = 0;
	while ((envvar_name[len] != '=') && (envvar_name[len] != '\0'))
		len++;
	return (len);
}
