/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:04 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/09 22:30:24 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_expand	*ft_get_expand_cmd(t_data *data, char *cmd);
static t_expand	*ft_get_expand_arg(t_data *data, char *arg);
static t_expand	*ft_get_expand_file(t_data *data, char *file);
static t_expand	*ft_get_expand_limter(t_data *data, char *limiter);

t_expand	*ft_get_expand(t_data *data, t_token *token)
{
	t_expand	*expand;

	if ((data == NULL) || (token == NULL) || (token->value == NULL))
		return (NULL);
	if (token->type == TOKEN_COMMAND)
		expand = ft_get_expand_cmd(data, token->value);
	else if (token->type == TOKEN_ARGUMENT)
		expand = ft_get_expand_arg(data, token->value);
	else if (token->type == TOKEN_LIMITER)
		expand = ft_get_expand_limter(data, token->value);
	else if (token->type == TOKEN_FILE)
		expand = ft_get_expand_file(data, token->value);
	else
		expand = NULL;
	return (expand);
}

static t_expand	*ft_get_expand_cmd(t_data *data, char *cmd)
{
	char		*value;
	t_list		*split;
	t_expand	*temp;
	t_expand	*expand;
	t_expand	*tail_p;

	ft_expand_init(&expand, &tail_p);
	split = ft_expand_split(data, cmd);
	if (split != NULL)
	{
		value = (char *) split->content;
		temp = ft_new_expand(TOKEN_COMMAND, value);
		ft_add_expand(&expand, &tail_p, temp);
		split = split->next;
	}
	while (split != NULL)
	{
		value = (char *) split->content;
		temp = ft_new_expand(TOKEN_ARGUMENT, value);
		ft_add_expand(&expand, &tail_p, temp);
		split = split->next;
	}
	return (expand);
}

static t_expand	*ft_get_expand_arg(t_data *data, char *arg)
{
	t_expand	*temp;
	t_expand	*expand;
	t_expand	*tail_p;
	t_list		*split;
	char		*value;

	ft_expand_init(&expand, &tail_p);
	split = ft_expand_split(data, arg);
	while (split != NULL)
	{
		value = (char *) split->content;
		temp = ft_new_expand(TOKEN_ARGUMENT, value);
		ft_add_expand(&expand, &tail_p, temp);
		split = split->next;
	}
	return (expand);
}

static t_expand	*ft_get_expand_file(t_data *data, char *file)
{
	t_expand	*temp;
	t_expand	*expand;
	t_expand	*tail_p;
	t_list		*split;
	char		*value;

	ft_expand_init(&expand, &tail_p);
	split = ft_expand_split(data, file);
	while (split != NULL)
	{
		value = (char *) split->content;
		temp = ft_new_expand(TOKEN_FILE, value);
		ft_add_expand(&expand, &tail_p, temp);
		split = split->next;
	}
	return (expand);
}

static t_expand	*ft_get_expand_limter(t_data *data, char *limiter)
{
	char		*trim;

	(void) data;
	trim = NULL;
	ft_trim_quotes(&trim, limiter);
	return (ft_new_expand(TOKEN_LIMITER, trim));
}
