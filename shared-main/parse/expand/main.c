/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:55 by hrazafia          #+#    #+#             */
/*   Updated: 2024/08/08 11:17:12 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

#define TESTPROMPT "tests> "

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

t_expand	*ft_get_expand(t_data *data, t_token *token)
{
	if ((data == NULL) || (token == NULL) || (token->value == NULL))
		return (NULL);
	
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	int			exit_status;
	t_list		*split;
	t_data		data;

	(void) argc;
	(void) argv;
	exit_status = 0;
	split = NULL;
	ft_data_init(&data, exit_status, env);
	line = ft_readline(TESTPROMPT);
	while (line != NULL)
	{
		if (ft_isempty(line) == false)
		{
			split = ft_expand_split(&data, line);
			ft_print_lst(split);
		}
		line = ft_readline(TESTPROMPT);
	}
	return (0);
}
