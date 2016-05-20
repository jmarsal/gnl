/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:57:01 by vquesnel          #+#    #+#             */
/*   Updated: 2016/03/19 18:17:07 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../get_next_line.h"

int			main(void)
{
	int		len;
	char	*str;

	len = 50;
	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	while (len--)
		str = strcat(str, "abcdefghijklmnopqrstuvwxyz\n");
	write(1, str, strlen(str));
	return (0);
}
