# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 18:21:35 by fquist            #+#    #+#              #
#    Updated: 2022/03/12 01:43:34 by dmontema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g

LIBFT_DIR	=	lib/Libft
MLX_LIB_DIR	=	lib/MLX42

MLX_LIB		=	-L./$(MLX_LIB_DIR) -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
LIBRARIES	= -L./$(LIBFT_DIR)/ -lft $(MLX_LIB)
INCLUDES	= -I./inc -I./$(LIBFT_DIR)/inc

SRC_DIR		=	./src
SRCS		=	main.c

OBJ_DIR		=	./obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ***************************************************************************** #
#	RULES																		#
# ***************************************************************************** #

all: $(NAME)

$(NAME): prep Libft MLX $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_LIB_DIR) fclean
	rm -f $(OBJS)
	rmdir $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

prep:
	@mkdir -p $(OBJ_DIR)

Libft:
	make -C $(LIBFT_DIR)

MLX:
	make -C $(MLX_LIB_DIR)

norm:
	@norminette -R CheckForbiddenSourceHeader include/*.h | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1
	@norminette -R CheckForbiddenSourceHeader src/*.c | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1

