/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal  <jmarsal @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 19:47:53 by jmarsal           #+#    #+#             */
/*   Updated: 2016/05/21 01:27:33 by jmarsal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_line	*add_elem(t_line **list, int fd)
{
	t_line	*new;
	t_line	*cur;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->fd = fd;
	new->line = ft_strnew(0);
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		cur = *list;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}

char		*get_line(t_line *list, char **line)
{
	char	*tmp;
	char	*text;
	int		i;

//	tmp = NULL;
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

static	int		read_file(int fd, t_line *list)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

//	tmp = NULL;
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

int				get_next_line(const int fd, char **line)
{
	static	t_line		*file;
	int					ret;
	t_line				*tmp;

	//tmp = NULL;
	if (!file)
		file = add_elem(&file, fd);
	tmp = file;
	if (fd < 0 || !line)
		return (-1);
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		if (tmp->next == NULL)
			add_elem(&file, fd);
		tmp = tmp->next;
	}
	if ((ret = read_file(fd, tmp)) == -1)
		return (-1);
	tmp->line = get_line(tmp, line);
	if (!ft_strlen(tmp->line) && !ft_strlen(*line) && !ret)
		return (0);
	else
		return (1);
}
