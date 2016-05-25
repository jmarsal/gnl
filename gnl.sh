# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/23 11:23:53 by vquesnel          #+#    #+#              #
#    Updated: 2016/05/25 15:24:21 by jmarsal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

make -C libft/
gcc -Wall -Wextra -Werror -o testgnl get_next_line.c launch/main.c -I libft/includes -I . libft/libft.a
make -C libft/ fclean
