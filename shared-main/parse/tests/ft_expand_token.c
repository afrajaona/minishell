/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/22 11:20:07 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_msh_expand.h"

void		ft_add_str_in_quotes(t_list **tmp, char *s, char q, size_t *index);
t_list		*ft_split_token(char *s);
t_expand	*ft_get_expand(t_data *data, t_list *split);
t_list		*ft_join_expand(t_expand *expand);

void	ft_add_str_in_quotes(t_list **temp, char *s, char delim, size_t *index)
{
	int	i;

	i = *index + 1;
	while ((s[i] != '\0') && (s[i] != delim))
	{
		ft_lstadd_back(temp, ft_lstnew(&s[i]));
		i++;
	}
	ft_lstadd_back(temp, ft_lstnew(&s[i]));
	*index = i;
}

t_list	*ft_split_token(char *s)
{
	size_t	i;
	t_list	*temp;
	t_list	*split;

	split = NULL;
	temp = NULL;
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		while ((ft_is_var(s, i) == false) && s[i] != '\0')
		{
			ft_lstadd_back(&temp, ft_lstnew(&s[i]));
			if (((s[i] == '\'') || (s[i] == '\"'))
				&& ft_quotes_isclose(s, s[i], i))
				ft_add_str_in_quotes(&temp, s, s[i], &i);
			i++;
			if ((s[i] == '\0') || ft_is_var(s, i))
			{
				ft_lstadd_back(&split, ft_lstnew(ft_lst_to_tab(temp)));
				temp = NULL;
			}
		}
		if ((s[i] != '\0') && ft_is_var(s, i))
		{
			ft_lstadd_back(&temp, ft_lstnew(&s[i]));
			i++;
			if (s[i] == '?')
			{
				ft_lstadd_back(&temp, ft_lstnew(&s[i]));
				i++;
			}
			else
			{
				while ((ft_isalpha(s[i]) || ft_isdigit(s[i]) || (s[i] == '_'))
					&& (s[i] != '\0'))
				{
					ft_lstadd_back(&temp, ft_lstnew(&s[i]));
					i++;
				}
			}
			ft_lstadd_back(&split, ft_lstnew(ft_lst_to_tab(temp)));
			temp = NULL;
		}
	}
	return (split);
}

t_expand	*ft_get_expand(t_data *data, t_list *split)
{
	t_token_type	type;
	char			*value;
	char			*s;
	t_expand		*expand;
	t_expand		*tail;

	tail = NULL;
	expand = NULL;
	while (split != NULL)
	{
		s = (char *) split->content;
		if ((s[0] == '$') && ft_is_var(s, 0))
			type = TOKEN_VAR;
		else
			type = TOKEN_STR;
		value = ft_expand(data, s);
		if ((type == TOKEN_VAR) && (value[0] == '\0'))
			split = split->next;
		else
		{
			ft_add_expand(&expand, &tail, ft_new_expand(type, value));
			split = split->next;
		}
	}
	return (expand);
}

t_list	*ft_join_expand(t_expand *expand)
{
	size_t	i;
	t_list	*token;
	t_list	*temp;
	char	*s;

	token = NULL;
	temp = NULL;
	if (expand == NULL)
		return (NULL);
	while (expand != NULL)
	{
		s = expand->value;
		if (expand->type == TOKEN_VAR)
		{
			i = 0;
			while (s[i] != '\0')
			{
				if (ft_isspace(s[i]))
				{
					if (temp)
					{
						ft_lstadd_back(&token, ft_lstnew(ft_to_str(temp)));
						temp = NULL;
					}
					while (ft_isspace(s[i]) && (s[i] != '\0'))
						i++;
				}
				else
				{
					ft_lstadd_back(&temp, ft_lstnew(&s[i]));
					i++;
				}
			}
		}
		else
		{
			if ((s[0] == '\0') && (expand->next == NULL))
			{
				ft_lstadd_back(&token, ft_lstnew(ft_to_str(temp)));
				temp = NULL;
			}
			i = 0;
			while (s[i] != '\0')
			{
				ft_lstadd_back(&temp, ft_lstnew(&s[i]));
				i++;
			}
		}
		expand = expand->next;
	}
	if (temp)
	{
		ft_lstadd_back(&token, ft_lstnew(ft_to_str(temp)));
		temp = NULL;
	}
	return (token);
}

t_list	*ft_expand_token(t_data *data, t_token_type token, char *s)
{
	t_expand	*temp;
	t_list		*expand;

	expand = NULL;
	if (token == TOKEN_LIMITER)
		ft_lstadd_back(&expand, ft_lstnew(ft_trim_quotes(s)));
	else
	{
		temp = ft_get_expand(data, ft_split_token(s));
		expand = ft_join_expand(temp);
	}
	return (expand);
}

/*
int	main(int argc, char **argv, char **env)
{
	char		*line;
	int			exit_status;
	t_list		*expand_token;
	t_data		data;

	(void) argc;
	(void) argv;
	exit_status = 0;
	expand_token = NULL;
	ft_init_data(&data, exit_status, env);
	line = readline(TESTPROMPT);
	while (line != NULL)
	{
		if (ft_isempty(line) == false)
		{
			add_history(line);
			expand_token = ft_expand_token(&data, TOKEN_LIMITER, line);
			ft_print_lst(expand_token);
		}
		line = readline(TESTPROMPT);
	}
	rl_clear_history();
	return (0);
}*/
