/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal <jmarsal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 19:47:53 by jmarsal           #+#    #+#             */
/*   Updated: 2016/05/13 14:40:41 by jmarsal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			gnl_read(t_gnl *gnl)
{
	int		result;

	if ((result = read(gnl->fd, gnl->buffer, BUFF_SIZE)) >= 0)
	{
		gnl->buffer[result] = '\0';
		gnl->rest_caract = 0;
	}
	if (result == -1)
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
		return (NULL);
	new_link->fd = fd;
	new_link->rest_caract = 0;
	new_link->buffer[0] = '\0';
	new_link->next = NULL;
	if (*other_files == NULL)
		*other_files = new_link;
	else
	{
		cur = *other_files;
		while (cur->next)
			cur = cur->next;
		cur->next = new_link;
	}
	return (new_link);
}

/*
**	1) Fill the string "rest_of_line" with the rest of the buffer after the \n.
**	2) Fill the string "tmp" which has not been copied to the string
**	"new_line" and being before the '\n'.
**	3) Concate in the string "new line" , the contents of line + tmp.
**	4 ) Stock the numbers of characters remaining after the \n to
**	"gnl->rest_caract".
*/

static int		get_the_rest_of_line(t_gnl *gnl, char **line)
{
	char		*rest_of_line;
	char		*tmp;
	char		*new_line;

	if ((rest_of_line = ft_strchr(&gnl->buffer[gnl->rest_caract], '\n'))
									!= NULL)
	{
		if ((tmp = ft_strsub(gnl->buffer, gnl->rest_caract,
				ft_abs(ft_strlen(rest_of_line) - ft_strlen(gnl->buffer)) -
					gnl->rest_caract)) == NULL)
			return (-1);
		if ((new_line = ft_strjoin(*line, tmp)) == NULL)
			return (-1);
		//free(*line);
		ft_bzero(*line, BUFF_SIZE);
		free(tmp);
		if ((*line = ft_memalloc(BUFF_SIZE)) == NULL)
			return (-1);
		//*line = ft_strdup(new_line);
		*line = new_line;
		//new_line = NULL;
		gnl->rest_caract = ft_abs(ft_strlen(rest_of_line) -
							ft_strlen(gnl->buffer)) + 1;
	}
	return (1);
}

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
{
	char	*str_get_before;
	char	*read_buffer;
	int		len;

	if ((*line = ft_strnew(0)) == NULL)
		return (-1);
	while ((read_buffer = ft_strchr(&gnl->buffer[gnl->rest_caract], '\n'))
									== NULL)
	{
		if ((str_get_before = ft_strjoin(*line, &gnl->buffer[gnl->rest_caract]))
									== NULL)
			return (-1);
	//	free(*line);
		//ft_memdel(&line);
		ft_bzero(*line, BUFF_SIZE);
		//*line = ft_strdup(str_get_before);
		//if ((*line = ft_strnew(BUFF_SIZE + 1)) == NULL)
		//	return (-1);
		*line = str_get_before;
		//str_get_before = NULL;
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
{
	static	t_gnl	*other_files = NULL;
	t_gnl			*current_file;
	int				ret_current_file;

	if (line == NULL)
		return (-1);
	current_file = other_files;
	while (current_file != NULL)
	{
		if (current_file->fd == fd)
			break ;
		current_file = current_file->next;
	}
	if (current_file == NULL)
	{
		if ((current_file = initializes_and_push(&other_files, fd)) == NULL)
			return (-1);
	}
	ret_current_file = read_line(current_file, line);
	if (ret_current_file < 1)
	{
		free(*line);
		*line = NULL;
	}
	return (ret_current_file);
}
