#include "exec.h"

t_arg	*init_arg(char *value)
{
	t_arg	*arg;

	arg = ft_calloc(sizeof(t_arg), 1);
	arg->value = value;
	arg->next = NULL;
	return (arg);
}

t_append	*append_value(char	*filename)
{
	t_list	*expand;
	t_append	*res;

	res = ft_calloc(sizeof(t_append), 1);
	expand = ft_calloc(sizeof(t_list), 1);
	res->n_arg = 1;
	res->filename = filename;
	expand->content = filename;
	expand->next = NULL;
	res->expand = expand;
	return (res);
}

t_input_redir	*input_redir_value(char *filename)
{
	t_list  *expand;
	t_input_redir	*res;

	res = ft_calloc(sizeof(t_input_redir), 1);
	expand = ft_calloc(sizeof(t_list), 1);
    res->n_arg = 1;
    res->filename = filename;
    expand->content = filename;
    expand->next = NULL;
    res->expand = expand;
	return (res);
}

t_output_redir	*output_redir_value(char *filename)
{
	t_list  *expand;
    t_output_redir  *res;

	res = ft_calloc(sizeof(t_output_redir), 1);
	expand = ft_calloc(sizeof(t_list), 1);
    res->n_arg = 1;
    res->filename = filename;
    expand->content = filename;
    expand->next = NULL;
    res->expand = expand;
    return (res);
}

t_redir	*init_redir(char *filename1, char *filename2)
{
	t_redir	*res;
	t_redir	*second;

	res = ft_calloc(sizeof(t_redir), 1);
	res->type = TOKEN_APPEND;
	res->data = (t_data *)append_value(filename1);
	second = ft_calloc(sizeof(t_redir), 1);
    second->type = TOKEN_INPUT_REDIR;
    second->data = (t_data *)input_redir_value(filename2);
	second->next = NULL;
	res->next = second;
	return (res);
}

void	init(t_cmd	*cmd, char *value)
{
	cmd->value = value;
	cmd->redir = init_redir("outfile", "test_exec.sh");
	cmd->arg = init_arg(NULL);
}
