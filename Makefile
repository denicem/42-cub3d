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
B_NAME		= cub3d_bonus

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	=	lib/Libft
MLX_LIB_DIR	=	lib/MLX42

MLX_LIB		= $(MLX_LIB_DIR)/libmlx42.a -lglfw -L "$(HOME)/.brew/Cellar/glfw/3.3.7/lib"
LIBRARIES	= -L./$(LIBFT_DIR) -lft $(MLX_LIB)

INCLUDES	= -I./inc -I./$(LIBFT_DIR)/inc -I./$(MLX_LIB_DIR)/include/MLX42

SRC_DIR		=	./src
SRCS		=	$(shell find $(SRC_DIR) -name "*.c" -execdir echo {} ";")

OBJ_DIR		=	./obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

B_SRC_DIR	=	./bonus_src
B_SRCS		=	$(shell find $(B_SRC_DIR) -name "*.c" -execdir echo {} ";")

B_OBJ_DIR	=	./bonus_obj
B_OBJS		=	$(addprefix $(B_OBJ_DIR)/, $(B_SRCS:.c=.o))
B_DEPS		=	$(OBJS:.o=.d)

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

-include $(DEPS) $(B_DEPS)

$(NAME): $(OBJS)
	@printf "$(BLUE)Linking objects and libraries to a binary file.\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"
	@echo "\t\t$(GREEN)$(BOLD)COMPLETE!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | install_lib prep
	@printf "$(BLUE)$(BOLD)\rCompiling: $(CYAN)$(notdir $<)\r"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
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
	@rm -rf $(B_OBJS) $(B_OBJ_DIR)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

fclean: clean
	@printf "$(MAGENTA)Removing binary file...\r$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(B_NAME)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)\n"

re: fclean all

bonus: $(B_NAME)

$(B_NAME): $(B_OBJS)
	@printf "$(BLUE)Linking objects and libraries to a binary file.\r"
	@$(CC) $(CFLAGS) $(B_OBJS) -o $(B_NAME) $(LIBRARIES)
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"
	@echo "\t\t$(GREEN)$(BOLD)COMPLETE!$(RESET)\n"

$(B_OBJ_DIR)/%.o: $(B_SRC_DIR)/%.c | install_lib prep_bonus
	@printf "$(BLUE)$(BOLD)\rCompiling: $(CYAN)$(notdir $<)\r"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@printf "\e[50C$(GREEN)[✓]\n$(RESET)"

install_lib:
	@make Libft
	@make MLX

prep:
	@mkdir -p $(OBJ_DIR)

prep_bonus:
	@mkdir -p $(B_OBJ_DIR)

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
	@norminette -R CheckForbiddenSourceHeader inc/*.h | grep --color=always 'Error!\|Error:' || echo "$(GREEN)Everything is OK!$(RESET)" >&1
	@norminette -R CheckForbiddenSourceHeader src/*.c | grep --color=always 'Error!\|Error:' || echo "$(GREEN)Everything is OK!$(RESET)" >&1
	@norminette -R CheckForbiddenSourceHeader bonus_src/*.c | grep --color=always 'Error!\|Error:' || echo "$(GREEN)Everything is OK!$(RESET)" >&1
