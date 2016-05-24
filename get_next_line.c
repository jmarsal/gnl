/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal <jmarsal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 19:47:53 by jmarsal           #+#    #+#             */
/*   Updated: 2016/05/24 16:23:31 by jmarsal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl		*new_file(const int fd)
{
	t_gnl	*new_link;

	if (!(new_link = (t_gnl*)malloc(sizeof(t_gnl))))
		return (NULL);
	new_link->fd = fd;
	new_link->line = ft_strnew(0);
	new_link->next = NULL;
	return (new_link);
}

int			read_file(int fd, t_gnl *list)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	tmp = NULL;
	ret = -42;
	while (!ft_strchr(list->line, EOL))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		else
		{
			buf[ret] = 0;
			tmp = list->line;
			if (!(list->line = ft_strjoin(list->line, buf)))
				return (-1);
			free(tmp);
		}
		if (ret < BUFF_SIZE)
			return (ret);
	}
	return (ret);
}

char		*get_line(t_gnl *list, char **line)
{
	char	*tmp;
	char	*text;
	int		i;

	tmp = NULL;
	i = 0;
	text = list->line;
	while (text[i])
	{
		if (text[i] == EOL)
		{
			*line = ft_strsub(text, 0, i);
			tmp = text;
			text = ft_strdup(text + (i + 1));
			free(tmp);
			return (text);
		}
		i++;
	}
	*line = ft_strdup(text);
	ft_strclr(text);
	ft_strclr(list->line);
	return (text);
}

int			get_next_line(int const fd, char **line)
{
	static	t_gnl		*list_files;
	int					ret;
	t_gnl				*current_file;

	if (!list_files)
		list_files = new_file(fd);
	current_file = list_files;
	if (fd < 0 || !line)
		return (-1);
	while (current_file)
	{
		if (current_file->fd == fd)
			break ;
		if (current_file->next == NULL)
			ft_lstadd((t_list**)&current_file, (t_list*) new_file(fd));
		current_file = current_file->next;
	}
	if ((ret = read_file(fd, current_file)) == -1)
		return (-1);
	current_file->line = get_line(current_file, line);
	if (!ft_strlen(current_file->line) && !ft_strlen(*line) && !ret)
		return (0);
	else
		return (1);
}
