# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 16:09:39 by mbatteux          #+#    #+#              #
#    Updated: 2024/03/09 23:31:02 by jolecomt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX42 = MLX42

CCC = src/cub3d.c\
	src/utils/cub3d_utils.c\
	src/utils/cub3d_utils2.c\
	src/utils/cub3d_utils3.c\
	src/maps/cub3d_map.c\
	src/maps/cub3d_map2.c\
	src/maps/cub3d_map3.c\
	src/minimap/cub3d_minimap.c\
	src/minimap/cub3d_minimap2.c\
	src/parser/cub3d_parser.c\
	src/parser/cub3d_parser2.c\
	src/parser/cub3d_free.c\
	src/raycasting/cub3d_raycaster.c\
	src/raycasting/cub3d_raycaster2.c\
	src/others/cub3d_keybindings.c\
	src/others/cub3d_texture.c\
	src/others/cub3d_color.c\
	src/others/ft_split.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c

OOO = $(CCC:.c=.o)\

MLX = MLX42/libmlx42.a

FLAG = -Wall -Wextra -Werror

LIBINCLUDE = -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OOO)
	cc $(OOO) $(FLAG) $(LIBINCLUDE) $(MLX) -o $(NAME) -g3
.c.o:
	cc -c $(FLAG) $< -o ${<:.c=.o} -g3
clean:
	rm -f $(OOO)
$(MLX42):
	git clone https://github.com/kodokaii/MLX42.git
	cmake $(MLX42) -B $(MLX42)
	make -C MLX42
cleanMLX42:
	rm -rf $(MLX42)
fclean: clean
	rm -f $(NAME)
re: fclean all
