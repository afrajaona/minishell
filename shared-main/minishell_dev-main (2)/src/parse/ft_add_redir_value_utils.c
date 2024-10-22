/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redir_value_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:25:10 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/10 01:05:26 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_redir	*ft_new_redir(t_token *token, t_type type)
{
	t_redir	*redir;
	int		res;

	if ((token == NULL) || ((type != TOKEN_INPUT_REDIR)
			&& (type != TOKEN_OUTPUT_REDIR)
			&& (type != TOKEN_HEREDOC)
			&& (type != TOKEN_APPEND)))
		return (NULL);
	redir = (t_redir *) malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	res = ft_get_redir_value(redir, type, token);
	if (res == -1)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

void	ft_redir_add_back(t_redir **redir_ptr, t_redir *redir)
{
	t_redir	*curr;

	if ((redir_ptr == NULL) || (redir == NULL))
		return ;
	if (*redir_ptr == NULL)
		*redir_ptr = redir;
	else
	{
		curr = *redir_ptr;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = redir;
	}
}
