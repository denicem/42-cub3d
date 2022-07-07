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
CFLAGS		= -Wall -Wextra -Werror#-g

LIBFT_DIR	=	lib/Libft
MLX_LIB_DIR	=	lib/MLX42

MLX_LIB		= $(MLX_LIB_DIR)/libmlx42.a -lglfw -L "$(HOME)/.brew/Cellar/glfw/3.3.7/lib"
LIBRARIES	= -L./$(LIBFT_DIR) -lft $(MLX_LIB)

INCLUDES	= -I./inc -I./$(LIBFT_DIR)/inc -I./$(MLX_LIB_DIR)/include/MLX42

SRC_DIR		=	./src
SRCS		=	$(shell find $(SRC_DIR) -name "*.c" -execdir echo {} ";")

OBJ_DIR		=	./obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ***************************************************************************** #
#	COLOURS																		#
# ***************************************************************************** #

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# ***************************************************************************** #
#	RULES																		#
# ***************************************************************************** #

all: $(NAME)

$(NAME): Libft MLX $(OBJS)
#@make Libft
#@make MLX
	@printf "$(BLUE)Linking objects and libraries to a binary file.\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"
	@echo "\t\t$(GREEN)$(BOLD)COMPLETE!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | prep
	@printf "$(BLUE)$(BOLD)\rCompiling: $(CYAN)$(notdir $<)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

clean:
	@printf "$(MAGENTA)Removing Libft library...\r"
	@make -C $(LIBFT_DIR) fclean >/dev/null
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"
	@printf "$(MAGENTA)Removing MLX library...\r"
	@make -C $(MLX_LIB_DIR) fclean >/dev/null
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"
	@printf "$(MAGENTA)Removing object files...\r$(RESET)"
	@rm -rf $(OBJS) $(OBJ_DIR)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

fclean: clean
	@printf "$(MAGENTA)Removing binary file...\r$(RESET)"
	@rm -rf $(NAME)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)\n"

re: fclean all

prep:
	@mkdir -p $(OBJ_DIR)

Libft:
	@printf "$(BLUE)Creating Libft library...\r"
	@make -C $(LIBFT_DIR) >/dev/null
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

MLX:
	@printf "$(BLUE)Creating MLX library...\r"
	@make -C $(MLX_LIB_DIR) >/dev/null
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

.PHONY: Libft MLX

norm:
	@norminette -R CheckForbiddenSourceHeader include/*.h | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1
	@norminette -R CheckForbiddenSourceHeader src/*.c | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1

