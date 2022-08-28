NAME = so_long
SO_LONG = so_long.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS =  -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
LIBS = ../libft/libft.a MLX42/libmlx42.a

SRC =	so_long check_key check_moves check_win cleanup \
		collectibles collision parsing setup wall_checks

SRCS = ./$(addsuffix .c, $(SRC))
OBJS = ./$(addsuffix .o, $(SRC))

$(NAME): $(SO_LONG)
	$(CC) $(CFLAGS) $(MLX_FLAGS) gnl/get_next_line.c gnl/get_next_line_utils.c $(SO_LONG) $(LIBS) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SO_LONG): $(OBJS)
	$(AR) $@ $^

clean: 
	rm -f $(OBJS) $(SO_LONG)

fclean: clean
	rm -f $(NAME)

all: $(NAME)

bonus: all

re: fclean all