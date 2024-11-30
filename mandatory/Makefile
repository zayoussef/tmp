NAME = cub3D

SRC = raycasting/main2d.c raycasting/tools.c raycasting/init_data.c raycasting/utils.c\
	parsing/get_next_line/get_next_line_utils.c raycasting/walls.c\
	parsing/get_next_line/get_next_line.c parsing/libft/ft_atoll.c \
	parsing/libft/ft_itoa.c parsing/libft/ft_memset.c parsing/libft/ft_putchar_fd.c \
	parsing/libft/ft_putendl_fd.c parsing/libft/ft_putstr_fd.c parsing/libft/ft_split.c \
	parsing/libft/ft_strchr.c parsing/libft/ft_strcmp.c parsing/libft/ft_strdup.c \
	parsing/libft/ft_strjoin.c parsing/libft/ft_strlen.c parsing/libft/ft_strncmp.c \
	parsing/libft/ft_strnstr.c parsing/parsing/check_args.c parsing/parsing/main.c \
	parsing/parsing/utils_2.c parsing/parsing/utils_map_2.c parsing/parsing/utils_map.c \
	parsing/parsing/utils_texture_2.c parsing/parsing/utils_texture.c parsing/parsing/utils.c \
	parsing/parsing/validate_file.c \

CC = cc 

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LDFLAGS = -lmlx -lXext -lX11 -lm

OBJ = $(SRC:.c=.o)

all: $(NAME)
    
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;34mLaunching build... 🚀\033[0m"
	@echo "\033[0;32mmake completed successfully! ✅\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@echo "\033[1;33mCleaning up... 🧹\033[0m"
	@echo "\033[0;32mclean completed successfully! ✅\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31mFull clean initiated... 🔥\033[0m"
	@echo "\033[0;32mfclean completed successfully! ✅\033[0m"

re: fclean all
	@echo "\033[1;35mRebuilding everything... 🔄\033[0m"
	@echo "\033[0;32mre completed successfully! ✅\033[0m"

.PHONY: all clean fclean re