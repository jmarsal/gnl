/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarsal <jmarsal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 13:56:22 by vquesnel          #+#    #+#             */
/*   Updated: 2016/05/10 22:53:47 by jmarsal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*line;

	line = NULL;
	fd = open(av[ac - 1], O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		ft_putstr(line);
		ft_putstr("\033[32;1m|---> \033[34;1m");
		ft_putnbr(ret);
		ft_putstr("\n\033[0m");
	}
	ft_putstr("\n");
	ft_putstr("\033[31;1;4mFINAL RET\033[0m\033[31;1m |---> \033[34;1m");
	ft_putnbr(ret);
	ft_putstr("\033[31;1m\n\n\033[0m");
	return (0);
}
