NAME = cub3D_bonus

SRC = raycasting_bonus/main2d_bonus.c raycasting_bonus/tools_bonus.c raycasting_bonus/init_data_bonus.c raycasting_bonus/utils_bonus.c\
	parsing_bonus/get_next_line/get_next_line_utils.c raycasting_bonus/walls_bonus.c raycasting_bonus/monster.c\
	parsing_bonus/get_next_line/get_next_line.c parsing_bonus/libft/ft_atoll.c \
	parsing_bonus/libft/ft_itoa.c parsing_bonus/libft/ft_memset.c parsing_bonus/libft/ft_putchar_fd.c \
	parsing_bonus/libft/ft_putendl_fd.c parsing_bonus/libft/ft_putstr_fd.c parsing_bonus/libft/ft_split.c \
	parsing_bonus/libft/ft_strchr.c parsing_bonus/libft/ft_strcmp.c parsing_bonus/libft/ft_strdup.c \
	parsing_bonus/libft/ft_strjoin.c parsing_bonus/libft/ft_strlen.c parsing_bonus/libft/ft_strncmp.c \
	parsing_bonus/libft/ft_strnstr.c parsing_bonus/parsing_bonus/check_args_bonus.c parsing_bonus/parsing_bonus/main_bonus.c \
	parsing_bonus/parsing_bonus/utils_2_bonus.c parsing_bonus/parsing_bonus/utils_map_2_bonus.c parsing_bonus/parsing_bonus/utils_map_bonus.c \
	parsing_bonus/parsing_bonus/utils_texture_2_bonus.c parsing_bonus/parsing_bonus/utils_texture_bonus.c parsing_bonus/parsing_bonus/utils_bonus.c \
	parsing_bonus/parsing_bonus/validate_file_bonus.c \

CC = cc 

MINILIB = ./minilibx-linux/libmlx_Linux.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

LDFLAGS = -lXext -lX11 -lm

OBJ = $(SRC:.c=.o)

all: $(NAME)
    
$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MINILIB) $(LDFLAGS)
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

.SILENT:
