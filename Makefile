
NAME = cub3d

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
	@echo "compiling $<"
	@$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJS_MAIN) $(OBJS)
	@$(MAKE) -C include/libft
	@$(MAKE) -C include/mlx
	@$(CC) $(CCFLAGS) $(SANITIZE) -framework OpenGL -framework AppKit  $(OBJS_MAIN) $(OBJS) include/libft/libft.a include/mlx/libmlx.a -o $(NAME)
	@echo "Cub3d done!"

linux: $(OBJS_MAIN) $(OBJS)
	@$(MAKE) -C include/libft
	@clang -Wall -Wextra -Werror $(OBJS_MAIN) $(OBJS) -lm -lbsd -lmlx -lXext -lX11 include/libft/libft.a -o $(NAME)
	@echo "Cub3d done!"	

all: $(NAME)

clean:
	@$(MAKE) clean -C include/libft
	@$(MAKE) clean -C include/mlx
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_MAIN)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C include/libft

re: fclean all

.PHONY: all clean fclean re
