/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal  <jmarsal @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 19:47:53 by jmarsal           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/05/21 00:50:54 by jmarsal          ###   ########.fr       */
=======
/*   Updated: 2016/05/17 15:46:27 by jmarsal          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_line	*add_elem(t_line **list, int fd)
{
	t_line	*new;
	t_line	*cur;

<<<<<<< HEAD
	if (!(new = (t_line *)malloc(sizeof(t_line))))
=======
	ft_bzero(gnl->buffer, BUFF_SIZE);
	if ((result = read(gnl->fd, gnl->buffer, BUFF_SIZE)) >= 0)
	{
		gnl->buffer[result] = '\0';
		gnl->rest_caract = 0;
	}
	else if (result == -1)
		return (-1);
	return (result);
}

/*
 **	Initializes a link to each new file and places it at the end of the list.
 */

static	t_gnl	*initializes_and_push(t_gnl **other_files, int fd)
{
	t_gnl	*new_link;
	t_gnl	*cur;

	if ((new_link = (t_gnl *)malloc(sizeof(t_gnl))) == NULL)
>>>>>>> master
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

<<<<<<< HEAD
int				read_file(int fd, t_line *list)
=======
/*
 **	1) Fill the string "rest_of_line" with the rest of the buffer after the \n.
 **	2) Fill the string "tmp" which has not been copied to the string
 **	"new_line" and being before the '\n'.
 **	3) Concate in the string "new line" , the contents of line + tmp.
 **	4 ) Stock the numbers of characters remaining after the \n to
 **	"gnl->rest_caract".
 */

static int		get_the_rest_of_line(t_gnl *gnl, char **line)
>>>>>>> master
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

<<<<<<< HEAD
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
=======
	if ((rest_of_line = ft_strchr(&gnl->buffer[gnl->rest_caract], '\n'))
			!= NULL)
	{
		if ((tmp = ft_strsub(gnl->buffer, gnl->rest_caract,
						ft_abs(ft_strlen(rest_of_line) - ft_strlen(gnl->buffer)) -
						gnl->rest_caract)) == NULL)
			return (-1);
		if ((new_line = ft_strjoin(*line, tmp)) == NULL)
			return (-1);
		//if (*line)
		//	free(*line);
		ft_bzero(*line, BUFF_SIZE);
		//if (tmp)
		//	free(tmp);
		*line = new_line;
		//if (new_line)
		//	free(new_line);
		gnl->rest_caract = ft_abs(ft_strlen(rest_of_line) -
				ft_strlen(gnl->buffer)) + 1;
>>>>>>> master
	}
	return (ret);
}

<<<<<<< HEAD
char		*get_line(t_line *list, char **line)
=======
/*
 **	1) initializes the string "line".
 **	2) check if '\n' is in the buffer otherwise, loop the read until there is
 **	not a '\n' and the concatenated string "str_get_before" of the buffer
 **	contents .
 **	3 ) Stock "str_get_before" content into the string "line" .
 **	4) if a '\n' is located , recovered the string "line" the entire contents
 **	of the string before '\n' with the function "get_the_rest_of_line".
 */

static	int		read_line(t_gnl *gnl, char **line)
>>>>>>> master
{
	char	*tmp;
	char	*text;
	int		i;

<<<<<<< HEAD
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

int			get_next_line(int const fd, char **line)
=======
	if ((*line = ft_strnew(0)) == NULL)
		return (-1);
	while ((read_buffer = ft_strchr(&gnl->buffer[gnl->rest_caract], '\n'))
			== NULL)
	{
		if ((str_get_before = ft_strjoin(*line, &gnl->buffer[gnl->rest_caract]))
				== NULL)
			return (-1);
		//if (*line)
		//	free(*line);
		*line = str_get_before;
		if ((len = gnl_read(gnl)) < 1)
			break ;
	}
	if (len == -1 || get_the_rest_of_line(gnl, line) == -1)
		return (-1);
	if (len == 0 && (*line)[0] == '\0')
		return (0);
	return (1);
}

/*
 **	1) fd compared with those stored in the list.
 **	2) if it is in the list then continues gnl otherwise create a new link and
 **	puts it at the end of the list.
 **	3) gets and returns the function return "read_line".
 */

int				get_next_line(const int fd, char **line)
>>>>>>> master
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
