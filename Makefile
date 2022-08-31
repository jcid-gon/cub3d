
NAME = cub3d.a

SRCS_MAIN = cub3d.c

SRCS =	srcs/map_reader.c		\
		srcs/map_reader_utils.c	

OBJS = $(SRCS:.c=.o)
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
CC = clang
CCFLAGS = -Wall -Werror -Wextra
SANITIZE = -fsanitize=address -g3
RM = rm -rf
MLX_PATH = include/mlx
LIBTF_PATH = include/libft

%.o: %.c
	@$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJS_MAIN) $(OBJS)
	@$(MAKE) -C include/libft
	@$(CC) $(CCFLAGS) $(SANITIZE) $(OBJS_MAIN) $(OBJS) include/libft/libft.a -o $(NAME)
	

all: $(NAME)

clean:
	@$(MAKE) clean -C include/libft
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_MAIN)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C include/libft

re: fclean all

.PHONY: all clean fclean re
