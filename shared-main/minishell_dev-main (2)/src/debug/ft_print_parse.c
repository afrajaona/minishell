/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:20:43 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:02:46 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

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

void	ft_print_parse_debug(t_parse *parse)
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
