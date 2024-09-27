/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/27 09:44:33 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parse.h"
#include "token.h"

#define PROMPT "tests> "

void	ft_print_lst(t_list *lst)
{
	char	*s;

	if (lst == NULL)
		ft_printf("NULL\n");
	while (lst != NULL)
	{
		s = (char *) lst->content;
		ft_printf("[%s]\n", s);
		lst = lst->next;
	}
}

void	ft_print_type(int type)
{
	if (type == TOKEN_PIPE)
		ft_printf("TOKEN_PIPE\n");
	else if (type == TOKEN_HEREDOC)
		ft_printf("TOKEN_HEREDOC\n");
	else if (type == TOKEN_APPEND)
		ft_printf("TOKEN_APPEND\n");
	else if (type == TOKEN_INPUT_REDIR)
		ft_printf("TOKEN_INPUT_REDIR\n");
	else if (type == TOKEN_OUTPUT_REDIR)
		ft_printf("TOKEN_OUTPUT_REDIR\n");
	else if (type == TOKEN_ARGUMENT)
		ft_printf("TOKEN_ARGUMENT\n");
	else if (type == TOKEN_FILE)
		ft_printf("TOKEN_FILE\n");
	else if (type == TOKEN_LIMITER)
		ft_printf("TOKEN_LIMITER\n");
	else
		ft_printf("TOKEN_COMMAND\n");
}

void	ft_print_expand(t_expand *expand)
{
	if (expand == NULL)
		ft_printf("token expand: NULL\n");
	while (expand != NULL)
	{
		ft_printf("token expand: [%s] : ", expand->value);
		ft_print_type(expand->type);
		expand = expand->next;
	}
}

void	ft_print_token(t_token *token)
{
	while (token != NULL)
	{
		ft_printf("\ntoken value : [%s] : ", token->value);
		ft_print_type(token->type);
		ft_print_expand(token->expand);
		token = token->next;
	}
}

char	*ft_readline(const char *prompt)
{
	size_t	i;
	char	*line;
	t_list	*temp;
	char	*s;

	ft_printf(prompt);
	s = get_next_line(0);
	if (s == NULL)
		return (NULL);
	temp = NULL;
	i = 0;
	while ((s[i] != '\n') && (s[i] != '\0'))
	{
		ft_lstadd_back(&temp, ft_lstnew(&s[i]));
		i++;
	}
	line = ft_to_str(temp);
	free(s);
	ft_clear_tmp(&temp);
	return (line);
}

t_parse	*ft_new_node(t_type type)
{
	t_parse	*new;

	new = (t_parse *) malloc(sizeof(t_parse));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_parse(t_parse **head_ptr, t_parse *parse)
{
	t_parse	*curr;

	if ((head_ptr == NULL) || (parse == NULL))
		return ;
	if (*head_ptr == NULL)
		*head_ptr = parse;
	else
	{
		curr = *head_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = parse;
		parse->prev = curr;
	}
}

void	ft_next_token(t_token **token_ptr, t_type type)
{
	t_token	*token;

	if (token_ptr == NULL)
		return ;
	token = *token_ptr;
	if ((token != NULL) && (type == TOKEN_COMMAND))
	{
		while ((token != NULL) && (token->type != TOKEN_PIPE))
			token = token->next;
	}
	if ((token != NULL) && (type == TOKEN_PIPE))
		token = token->next;
	*token_ptr = token;
}

t_pipe	*ft_new_pipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) malloc(sizeof(t_pipe));
	if (pipe == NULL)
		return (NULL);
	return (pipe);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->value = NULL;
	cmd->redir = NULL;
	cmd->arg = NULL;
	return (cmd);
}

void	ft_add_pipe_node(t_parse **parse_ptr, t_token **token_ptr)
{
	t_parse	*node;

	node = ft_new_node(TOKEN_PIPE);
	if (node == NULL)
	{
		ft_next_token(token_ptr, TOKEN_PIPE);
		return ;
	}
	node->data.pipe = ft_new_pipe();
	if (node->data.pipe == NULL)
	{
		free(node);
		ft_next_token(token_ptr, TOKEN_PIPE);
		return ;
	}
	ft_next_token(token_ptr, TOKEN_PIPE);
	ft_add_parse(parse_ptr, node);
}

t_arg	*ft_new_arg(char *value)
{
	t_arg	*arg;

	arg = (t_arg *) malloc(sizeof(t_arg));
	if (arg == NULL)
		return (NULL);
	arg->value = value;
	arg->next = NULL;
	return (arg);
}

void	ft_arg_add_back(t_arg **arg_ptr, t_arg *new)
{
	t_arg	*curr;

	if ((arg_ptr == NULL) || (new == NULL))
		return ;
	if (*arg_ptr == NULL)
		*arg_ptr = new;
	else
	{
		curr = *arg_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void	ft_redir_add_back(t_redir **redir_ptr, t_redir *new)
{
	t_redir	*curr;

	if ((redir_ptr == NULL) || (new == NULL))
		return ;
	if (*redir_ptr == NULL)
		*redir_ptr = new;
	else
	{
		curr = *redir_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

t_list	*ft_get_token_expand(t_expand *expand)
{
	t_list	*values;

	values = NULL;
	while (expand != NULL)
	{
		ft_add_content(&values, expand->value);
		expand = expand->next;
	}
	return (values);
}

int	ft_get_input_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_INPUT_REDIR))
		return (-1);
	expand = ft_get_token_expand(token->expand);
	if (expand == NULL)
		return (-1);
	redir->type = type;
	redir->value.input_redir.n_arg = ft_lstsize(expand);
	redir->value.input_redir.filename = token->value;
	redir->value.input_redir.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_output_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_OUTPUT_REDIR))
		return (-1);
	expand = ft_get_token_expand(token->expand);
	if (expand == NULL)
		return (-1);
	redir->type = type;
	redir->value.output_redir.n_arg = ft_lstsize(expand);
	redir->value.output_redir.filename = token->value;
	redir->value.output_redir.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_append_redir(t_redir *redir, t_type type, t_token *token)
{
	t_list	*expand;

	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_APPEND))
		return (-1);
	expand = ft_get_token_expand(token->expand);
	if (expand == NULL)
		return (-1);
	redir->type = type;
	redir->value.append.n_arg = ft_lstsize(expand);
	redir->value.append.filename = token->value;
	redir->value.append.expand = expand;
	redir->next = NULL;
	return (0);
}

int	ft_get_heredoc_redir(t_redir *redir, t_type type, t_token *token)
{
	if ((redir == NULL) || (token == NULL)
		|| (type != TOKEN_HEREDOC))
		return (-1);
	redir->type = type;
	redir->value.heredoc.is_exec = false;
	redir->value.heredoc.limiter = token->value;
	redir->value.heredoc.expand = token->expand->value;
	redir->next = NULL;
	return (0);
}

int	ft_get_redir_value(t_redir *redir, t_type type, t_token *token)
{
	int	res;

	if ((redir == NULL) || (token == NULL))
		return (-1);
	if ((type == TOKEN_INPUT_REDIR) && (token->type == TOKEN_FILE))
		res = ft_get_input_redir(redir, TOKEN_INPUT_REDIR, token);
	else if ((type == TOKEN_OUTPUT_REDIR) && (token->type == TOKEN_FILE))
		res = ft_get_output_redir(redir, TOKEN_OUTPUT_REDIR, token);
	else if ((type == TOKEN_HEREDOC) && (token->type == TOKEN_LIMITER))
		res = ft_get_heredoc_redir(redir, TOKEN_HEREDOC, token);
	else if ((type == TOKEN_APPEND) && (token->type == TOKEN_FILE))
		res = ft_get_append_redir(redir, TOKEN_APPEND, token);
	else
		return (-1);
	return (res);
}

t_redir	*ft_new_redir(t_token *token, t_type type)
{
	t_redir		*redir;

	if ((token == NULL)
		|| ((type != TOKEN_INPUT_REDIR)
		&& (type != TOKEN_OUTPUT_REDIR)
		&& (type != TOKEN_HEREDOC)
		&& (type != TOKEN_APPEND)))
		return (NULL);
	redir = (t_redir *) malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	if (ft_get_redir_value(redir, type, token) == -1)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

void	ft_add_cmd_value(t_cmd *cmd, t_token **token_ptr)
{
	t_token		*token;
	t_arg		*arg;
	t_redir		*redir;

	token = *token_ptr;
	while ((token != NULL) && (token->type != TOKEN_PIPE))
	{
		if ((token->type == TOKEN_COMMAND) && (token->expand != NULL))
		{
			if (token->expand->type == TOKEN_COMMAND)
			{
				cmd->value = token->expand->value;
				token->expand = token->expand->next;
			}
			while ((token->expand != NULL)
				&& (token->expand->type == TOKEN_ARGUMENT))
			{
				arg = ft_new_arg(token->expand->value);
				ft_arg_add_back(&cmd->arg, arg);
				token->expand = token->expand->next;
			}
		}
		if ((token->type == TOKEN_ARGUMENT) && (token->expand != NULL))
		{
			while (token->expand != NULL)
			{
				arg = ft_new_arg(token->expand->value);
				ft_arg_add_back(&cmd->arg, arg);
				token->expand = token->expand->next;
			}
		}
		if ((token->type == TOKEN_INPUT_REDIR) && (token->next != NULL) && (token->next->type == TOKEN_FILE))
		{
			token = token->next;
			redir = ft_new_redir(token, TOKEN_INPUT_REDIR);
			ft_redir_add_back(&cmd->redir, redir);
		}
		if ((token->type == TOKEN_HEREDOC) && (token->next != NULL) && (token->next->type == TOKEN_LIMITER))
		{
			token = token->next;
			redir = ft_new_redir(token, TOKEN_HEREDOC);
			ft_redir_add_back(&cmd->redir, redir);
		}
		if ((token->type == TOKEN_OUTPUT_REDIR) && (token->next != NULL) && (token->next->type == TOKEN_FILE))
		{
			token = token->next;
			redir = ft_new_redir(token, TOKEN_OUTPUT_REDIR);
			ft_redir_add_back(&cmd->redir, redir);
		}
		if ((token->type == TOKEN_APPEND) && (token->next != NULL) && (token->next->type == TOKEN_FILE))
		{
			token = token->next;
			redir = ft_new_redir(token, TOKEN_APPEND);
			ft_redir_add_back(&cmd->redir, redir);
		}
		if (token != NULL)
			token = token->next;
	}
	*token_ptr = token;
}

void	ft_add_cmd_node(t_parse **parse_ptr, t_token **token_ptr)
{
	t_parse	*node;

	node = ft_new_node(TOKEN_COMMAND);
	if (node == NULL)
	{
		ft_next_token(token_ptr, TOKEN_COMMAND);
		return ;
	}
	node->data.cmd = ft_new_cmd();
	if (node->data.cmd == NULL)
	{
		free(node);
		ft_next_token(token_ptr, TOKEN_COMMAND);
		return ;
	}
	ft_add_cmd_value(node->data.cmd, token_ptr);
	ft_add_parse(parse_ptr, node);
}

void	ft_get_parse(t_parse **parse_ptr, t_token *token)
{
	t_parse	*temp;

	temp = NULL;
	if ((parse_ptr == NULL) || (token == NULL))
		return ;
	while (token != NULL)
	{
		if (token->type == TOKEN_PIPE)
			ft_add_pipe_node(&temp, &token);
		else
			ft_add_cmd_node(&temp, &token);
	}
	ft_add_parse(parse_ptr, temp);
}

void	ft_parse(t_data *data, t_parse **cmds, char *line)
{
	t_token	*token;
	t_parse	*parse;

	parse = NULL;
	ft_get_token(data, &token, line);
	ft_get_parse(&parse, token);
	*cmds = parse;
}

void	ft_print_parse(t_parse *parse)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (parse == NULL)
		ft_printf("NULL");
	while (parse != NULL)
	{
		if (parse->type == TOKEN_PIPE)
		{
			ft_printf("\npipe%d\n\n", j + 1);
			j++;
		}
		if (parse->type == TOKEN_COMMAND)
		{
			ft_printf("cmd%d:\n", i + 1);
			ft_printf("  val: %s\n", parse->data.cmd->value);
			while (parse->data.cmd->arg != NULL)
			{
				ft_printf("  arg: %s\n", parse->data.cmd->arg->value);
				parse->data.cmd->arg = parse->data.cmd->arg->next;
			}
			i++;
			while (parse->data.cmd->redir != NULL)
			{	
				if (parse->data.cmd->redir->type == TOKEN_INPUT_REDIR)
				{
					ft_printf("  input redir:\n");
					ft_printf("    n_arg: %d\n", parse->data.cmd->redir->value.input_redir.n_arg);
					ft_printf("    filename: %s\n", parse->data.cmd->redir->value.input_redir.filename);
					if (parse->data.cmd->redir->value.input_redir.expand == NULL)
						ft_printf("    expand: NULL\n");
					else
						ft_printf("    expand:\n");
					k = 0;
					while (parse->data.cmd->redir->value.input_redir.expand != NULL)
					{
						ft_printf("      filename%d: %s\n", k + 1, (char *) parse->data.cmd->redir->value.input_redir.expand->content);
						parse->data.cmd->redir->value.input_redir.expand = parse->data.cmd->redir->value.input_redir.expand->next;
						k++;
					}
				}
				if (parse->data.cmd->redir->type == TOKEN_OUTPUT_REDIR)
				{
					ft_printf("  output redir:\n");
					ft_printf("    n_arg: %d\n", parse->data.cmd->redir->value.output_redir.n_arg);
					ft_printf("    filename: %s\n", parse->data.cmd->redir->value.output_redir.filename);
					if (parse->data.cmd->redir->value.output_redir.expand == NULL)
						ft_printf("    expand: NULL\n");
					else
						ft_printf("    expand:\n");
					k = 0;
					while (parse->data.cmd->redir->value.output_redir.expand != NULL)
					{
						ft_printf("      filename%d: %s\n", k + 1, (char *) parse->data.cmd->redir->value.output_redir.expand->content);
						parse->data.cmd->redir->value.output_redir.expand = parse->data.cmd->redir->value.output_redir.expand->next;
						k++;
					}
				}
				if (parse->data.cmd->redir->type == TOKEN_APPEND)
				{
					ft_printf("  append:\n");
					ft_printf("    n_arg: %d\n", parse->data.cmd->redir->value.append.n_arg);
					ft_printf("    filename: %s\n", parse->data.cmd->redir->value.append.filename);
					if (parse->data.cmd->redir->value.append.expand == NULL)
						ft_printf("    expand: NULL\n");
					else
						ft_printf("    expand:\n");
					k = 0;
					while (parse->data.cmd->redir->value.append.expand != NULL)
					{
						ft_printf("      filename%d: %s\n", k + 1, (char *) parse->data.cmd->redir->value.append.expand->content);
						parse->data.cmd->redir->value.append.expand = parse->data.cmd->redir->value.append.expand->next;
						k++;
					}
				}
				if (parse->data.cmd->redir->type == TOKEN_HEREDOC)
				{
					ft_printf("  heredoc:\n");
					if (parse->data.cmd->redir->value.heredoc.is_exec == false)
						ft_printf("    is_exec: %s\n", "false");
					else
						ft_printf("    is_exec: %s\n", "true");
					ft_printf("    limiter: %s\n", parse->data.cmd->redir->value.heredoc.limiter);
					if (parse->data.cmd->redir->value.heredoc.expand == NULL)
						ft_printf("    expand: NULL\n");
					else
						ft_printf("    expand: %s\n", parse->data.cmd->redir->value.heredoc.expand);
				}
				parse->data.cmd->redir = parse->data.cmd->redir->next;
			}
		}
		parse = parse->next;
	}
}

void	ft_print_parse2(t_parse *parse)
{
	t_parse	*prev;
	t_parse	*next;

	ft_printf("\n");
	if (parse == NULL)
		ft_printf("NULL");
	while (parse != NULL)
	{
		if (parse->type == TOKEN_COMMAND)
		{
			prev = parse->prev;
			if (prev == NULL)
				ft_printf("NULL");
			else if (prev->type == TOKEN_PIPE)
				ft_printf("|");
			else
				ft_printf("cmd");
			ft_printf(" <-- cmd --> ");
			next = parse->next;
			if (next == NULL)
				ft_printf("NULL");
			else if (next->type == TOKEN_PIPE)
				ft_printf("|");
			else
				ft_printf("cmd");
			ft_printf("\n");
		}
		parse = parse->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_parse		*cmds;
	t_data		data;

	(void) argc;
	(void) argv;
	ft_data_init(&data, 0, env);
	line = ft_readline(PROMPT);
	while (line != NULL)
	{
		if (ft_isempty(line))
			free(line);
		else
		{
			ft_parse(&data, &cmds, line);
			ft_print_parse(cmds);
			//ft_print_parse2(cmds);
			free(line);
		}
		line = ft_readline(PROMPT);
	}
	ft_free_data(&data);
	return (0);
}
