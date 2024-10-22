/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:31:53 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:44:02 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_content	*ft_sub_content(t_content *content, size_t start);

t_content	*ft_new_content(char *s, size_t len)
{
	t_content	*new;

	new = (t_content *) malloc(sizeof(t_content));
	if (new == NULL)
		return (NULL);
	new->value = s;
	new->len = len;
	new->next = NULL;
	return (new);
}

void	ft_clear_content(t_content **content)
{
	t_content	*head;
	t_content	*next;

	if (content == NULL)
		return ;
	head = *content;
	while (head != NULL)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
	*content = NULL;
}

size_t	ft_len_content(t_content *content)
{
	size_t	len;
	size_t	i;

	if (content == NULL)
		return (0);
	len = 0;
	while (content->next != NULL)
	{
		len = len + content->len;
		content = content->next;
	}
	i = 0;
	while ((content->value[i] != '\n')
		&& (content->value[i] != '\0'))
		i++;
	if (content->value[i] == '\n')
		i++;
	return (len + i);
}

void	ft_clean_buffer(t_content **content)
{
	size_t		i;
	t_content	*temp;

	if ((content == NULL) || (*content == NULL))
		return ;
	while ((*content)->next != NULL)
	{
		temp = (*content)->next;
		free((*content)->value);
		free(*content);
		*content = temp;
	}
	i = 0;
	while (((*content)->value[i] != '\n') && ((*content)->value[i] != '\0'))
		i++;
	if ((*content)->value[i] == '\n')
		i++;
	temp = *content;
	if (i < (*content)->len)
		*content = ft_sub_content(*content, i);
	else
		*content = NULL;
	free(temp->value);
	free(temp);
}

static t_content	*ft_sub_content(t_content *content, size_t start)
{
	size_t		i;
	t_content	*new;
	char		*s;
	size_t		len;

	len = content->len - start;
	s = (char *) malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = content->value[start + i];
		i++;
	}
	s[i] = '\0';
	new = ft_new_content(s, len);
	if (new == NULL)
	{
		free(s);
		return (NULL);
	}
	return (new);
}
