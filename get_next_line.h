/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal  <jmarsal @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 19:34:22 by jmarsal           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/05/21 00:54:50 by jmarsal          ###   ########.fr       */
=======
/*   Updated: 2016/05/17 15:40:18 by jmarsal          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
<<<<<<< HEAD
# define BUFF_SIZE 1
# define EOL '\n'
=======
# define BUFF_SIZE 1024

>>>>>>> master
# include "libft.h"
# include <unistd.h>

typedef struct		s_line
{
	int				fd;
	char			*line;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
