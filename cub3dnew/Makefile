NAME		= cub3D

SRC 		= main.c parsing1.c put_text_struct.c \
			parsing2.c parsing_map_elements.c \
			check_config_elements.c thom.c \
			ft_player_pos.c get_next_line.c \
			get_next_line_utils.c utils.c raycasting.c \
			utils2.c moves.c draw.c parsing_color.c \
			free_parsing.c utils_parsing.c \
			parsing_map_elements2.c parsing_directions.c \
			parsing_textures.c put_text_struct2.c \
			utils_parsing_2.c put_text_utils.c \
			parsing_color2.c printerror_rgbhex.c


CC 			= cc 

OBJ_DIR		= obj

OBJ 		= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

RM			= rm -rf

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	${CC} -g -Wall -Werror -Wextra -I/usr/include -Imlx_linux -O3 -c $< -o $@

all	: $(NAME)

$(NAME): $(OBJ)
				@make -C mlx_linux
				$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean:
				make -C mlx_linux clean
				$(RM) $(OBJ)
				$(RM) $(OBJ_DIR)

fclean:			clean
					make -C mlx_linux clean
					$(RM) $(NAME)
					$(RM) $(OBJ_DIR)

re:				fclean all

.PHONY:			all clean fclean re 
