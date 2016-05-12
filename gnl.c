/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal <jmarsal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 23:54:46 by jmarsal           #+#    #+#             */
/*   Updated: 2016/05/11 01:32:49 by jmarsal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	new_link->nb_lignes = 0;
	new_link->tab = NULL;
	new_link->i = 0;
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

static int			gnl_read(t_gnl *gnl)
{
	int		result;
	int		i;

	i = 0;
	if ((result = read(gnl->fd, gnl->buffer, BUFF_SIZE)) >= 0)
	{
		gnl->buffer[result] = '\0';
		gnl->rest_caract = 0;
	}
	if (result == -1)
		return (-1);
	while (gnl->buffer[i])
	{
		if (gnl->buffer[i] == '\n')
			gnl->nb_lignes += 1;
		i++;
	}
	return (result);
}

static	int		read_line(t_gnl *gnl, char **line)
{
	int		len;

	while ((len = gnl_read(gnl)) != 0)
	{
		gnl->big_buffer = 
	}
	if (len < 0)
		return (-1);
	if (gnl->tab == NULL)
	{
		if ((gnl->tab = (char**)malloc(sizeof(char*) + 1)) == NULL)
			return (-1);
		gnl->tab = ft_strsplit((const char*)gnl->buffer, '\n');
	}
	if (gnl->tab != 0)
	{
		free(*line);
		*line = gnl->tab[gnl->i++];
		return (1);
	}
	return (0);
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
	// if ((ret_current_file = read_line(current_file, line)) < 1)
	if (ret_current_file < 1)
	{
		free(*line);
		*line = NULL;
	}
	return (ret_current_file);
}
