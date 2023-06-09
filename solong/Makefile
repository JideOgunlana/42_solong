NAME = so_long
SO_LONG = so_long.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra
# gcc main.c ... libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
MLX_FLAGS = -I include -lglfw -ldl -pthread -lm -L "/Users/$(USER)/.brew/opt/glfw/lib/"
LIBS = ./includes/libft/libft.a MLX42/libmlx42.a

SRC =	so_long check_key check_moves check_win cleanup \
		collectibles collision parsing setup wall_checks

SRCS = ./$(addsuffix .c, $(SRC))
OBJS = ./$(addsuffix .o, $(SRC))

$(NAME): $(SO_LONG) $(LIBS)
	$(CC)  includes/gnl/get_next_line.c includes/gnl/get_next_line_utils.c $(SO_LONG) $(LIBS) $(CFLAGS) $(MLX_FLAGS) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SO_LONG): $(OBJS)
	$(AR) $@ $^

$(LIBS):
	make -C includes/libft
	make -C MLX42


clean: 
	rm -f $(OBJS) $(SO_LONG)
	make clean -C includes/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C includes/libft

all: $(NAME)

bonus: all

re: fclean all
