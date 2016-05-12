make -C ../get_next_line/libft/ fclean
make -C ../get_next_line/libft/
cp ./main.c ../get_next_line
gcc -Wall -Wextra -Werror -I ../get_next_line/libft/includes -o get_next_line.o -c ../get_next_line/get_next_line.c
gcc -Wall -Wextra -Werror -I ../get_next_line/libft/includes -o main.o -c main.c
rm ../get_next_line/main.c
gcc -o test_gnl main.o get_next_line.o -I ../get_next_line/libft/includes -L ../get_next_line/libft/ -lft
rm *o && make -C ../get_next_line/libft/ fclean
