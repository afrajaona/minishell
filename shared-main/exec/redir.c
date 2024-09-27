/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arajaona <arajaona@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:19:17 by arajaona          #+#    #+#             */
/*   Updated: 2024/09/23 14:53:39 by arajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_error(char *filename, char *error)
{
	int	tmp_fd;

	tmp_fd = dup(1);
	dup2(2, 1);
	printf("minishell: %s: %s\n", filename, error);
	dup2(tmp_fd, 1);
	exit(EXIT_FAILURE);
}

void	ft_append(t_append *arg)
{
	int 	fd;
	char	*name;

	if (arg->n_arg != 1)
		redir_error(arg->filename, "ambiguous redirect");
	name = (char *)arg->expand->content;
    fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("creating outfile");
        return ;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("redirecting output");
        return ;
    }
}

void	ft_redir_output(t_output_redir *redir)
{
	int		fd;
	char	*name;

	if (redir->n_arg != 1)
		redir_error(redir->filename, "ambiguous redirect");
	name = (char *)redir->expand->content;
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("creating outfile");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("redirecting output");
		return ;
	}
}

void	ft_redir_input(t_input_redir *redir)
{
	char	*name;
	int		fd;

	if (redir->n_arg != 1)
		redir_error(redir->filename, "ambiguous redirect");
	name = (char *)redir->expand->content;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		redir_error(name, strerror(errno));
	if (dup2(fd, STDIN_FILENO))
	{
		perror("input redirection");
		return ;
	}
}

void	ft_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == TOKEN_INPUT_REDIR)
			ft_redir_input((t_input_redir *)temp->data);
		else if (temp->type == TOKEN_OUTPUT_REDIR)
			ft_redir_output((t_output_redir *)temp->data);
		else if (temp->type == TOKEN_APPEND)
			ft_append((t_append *)temp->data);
		else if (temp->type == TOKEN_HEREDOC)
		{
			if (dup2(((t_heredoc *)temp->data)->heredocfd[0], STDOUT_FILENO) == -1)
			{
				perror("heredoc redir");
				return ;
			}
		}
		temp = temp->next;
	}
}
