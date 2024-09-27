/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:53:33 by hrazafia          #+#    #+#             */
/*   Updated: 2024/09/02 18:52:01 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	ft_token_init(t_token **head_ptr, t_token **tail_ptr)
{
	*head_ptr = NULL;
	*tail_ptr = NULL;
}

t_token	*ft_new_token(t_type type, char *value)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->expand = NULL;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **head_ptr, t_token **tail_ptr, t_token *token)
{
	t_token	*tail;

	if ((head_ptr == NULL) || (tail_ptr == NULL) || (token == NULL))
		return ;
	tail = *tail_ptr;
	if (*head_ptr == NULL)
	{
		*head_ptr = token;
		*tail_ptr = token;
	}
	else
	{
		token->prev = tail;
		tail->next = token;
		*tail_ptr = token;
	}
}

void	ft_clear_token(t_token **token)
{
	t_token	*curr;
	t_token	*next;

	if (token == NULL)
		return ;
	curr = *token;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*token = NULL;
}
