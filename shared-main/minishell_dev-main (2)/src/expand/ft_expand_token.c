/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:35:48 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:04:02 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_bool	ft_is_valid_name(char *s);
static char		*ft_get_var_name(char *s);
static t_bool	ft_check_varname(char *value);
static void		ft_expand_export_arg(t_data *data, t_token **token_ptr);

void	ft_expand_token(t_data *data, t_token *token)
{
	char	*value;

	if ((data == NULL) || (token == NULL))
		return ;
	while (token != NULL)
	{
		if ((token->type == TOKEN_COMMAND)
			&& ft_check_builtin("export", token->value))
		{
			value = ft_strdup(token->value);
			token->expand = ft_new_expand(TOKEN_COMMAND, value);
			token = token->next;
			ft_expand_export_arg(data, &token);
		}
		else
			token->expand = ft_get_expand(data, token);
		if (token != NULL)
			token = token->next;
	}
}

static t_bool	ft_check_varname(char *value)
{
	char	*s;
	t_bool	res;

	if (value == NULL)
		return (false);
	s = ft_get_var_name(value);
	if (s == NULL)
		return (false);
	res = ft_is_valid_name(s);
	free(s);
	return (res);
}

static void	ft_expand_export_arg(t_data *data, t_token **token_ptr)
{
	t_token	*token;
	char	*s;

	if ((token_ptr == NULL) || (*token_ptr == NULL))
		return ;
	token = *token_ptr;
	while ((token != NULL) && (token->type == TOKEN_ARGUMENT)
		&& (token->type != TOKEN_PIPE))
	{
		if (ft_check_varname(token->value))
		{
			ft_expand(data, &s, token->value);
			token->expand = ft_new_expand(TOKEN_ARGUMENT, s);
		}
		else
			token->expand = ft_get_expand(data, token);
		token = token->next;
	}
	*token_ptr = token;
}

static char	*ft_get_var_name(char *s)
{
	size_t	i;
	t_list	*temp;
	char	*var_name;

	if (s == NULL)
		return (NULL);
	i = 0;
	temp = NULL;
	while ((s[i] != '=') && (s[i] != '\0'))
	{
		ft_add_content(&temp, &s[i]);
		i++;
	}
	var_name = ft_lst_to_tab(temp);
	ft_clear_temp_list(&temp);
	return (var_name);
}

static t_bool	ft_is_valid_name(char *s)
{
	size_t	i;

	if (s == NULL)
		return (false);
	i = 0;
	if ((ft_isalpha(s[i]) == false) && (s[i] != '_'))
		return (false);
	i++;
	while (s[i] != '\0')
	{
		if ((ft_isalpha(s[i]) || ft_isdigit(s[i]) || (s[i] == '_'))
			&& (s[i] != '\0'))
			i++;
		else
			return (false);
	}	
	return (true);
}
