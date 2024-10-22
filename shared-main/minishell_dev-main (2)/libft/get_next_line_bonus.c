/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:31:53 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:43:54 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_check_buffer(t_content *buffer);
static t_content	*ft_read(int fd, t_content **buffer);
static t_content	*ft_add_content(t_content **buffer, int fd);
static char			*ft_get_line(t_content *buffer);

char	*get_next_line(int fd)
{
	char				*line;
	static t_content	*buffer[1024];

	if ((BUFFER_SIZE <= 0) || (fd < 0))
		return (NULL);
	if (ft_check_buffer(buffer[fd]) == 0)
		ft_add_content(&buffer[fd], fd);
	line = ft_get_line(buffer[fd]);
	ft_clean_buffer(&buffer[fd]);
	return (line);
}

static int	ft_check_buffer(t_content *buffer)
{
	size_t	i;

	if (buffer == NULL)
		return (0);
	i = 0;
	while ((buffer->value[i] != '\n') && (buffer->value[i] != '\0'))
		i++;
	if (buffer->value[i] == '\n')
		return (1);
	else
		return (0);
}

static t_content	*ft_read(int fd, t_content **buffer)
{
	char		*buf;
	int			ret;
	t_content	*content;

	buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	if ((ret == 0) || (ret == -1))
	{
		if (ret == -1)
			ft_clear_content(buffer);
		free(buf);
		return (NULL);
	}
	buf[ret] = '\0';
	content = ft_new_content(buf, ret);
	if (content == NULL)
	{
		free(buf);
		return (NULL);
	}
	return (content);
}

static t_content	*ft_add_content(t_content **buffer, int fd)
{
	t_content	*head;
	t_content	*content;

	content = ft_read(fd, buffer);
	while (content != NULL)
	{
		if (*buffer == NULL)
			*buffer = content;
		else
		{
			head = *buffer;
			while (head->next != NULL)
				head = head->next;
			head->next = content;
		}
		if (ft_check_buffer(content))
			break ;
		content = ft_read(fd, buffer);
	}
	return (*buffer);
}

static char	*ft_get_line(t_content *buffer)
{
	size_t	i;
	size_t	j;
	char	*line;
	size_t	len;

	len = ft_len_content(buffer);
	if (len == 0)
		return (NULL);
	line = (char *) malloc((len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		line[i++] = buffer->value[j++];
		if (buffer->value[j] == '\0')
		{
			buffer = buffer->next;
			j = 0;
		}
	}
	line[len] = '\0';
	return (line);
}
