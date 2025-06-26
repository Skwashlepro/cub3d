SEPIA = \033[38;5;180m
BLACK = \033[0;30m
WHITE = \033[1;37m
GRAY = \033[0;37m
RESET = \033[0m
BOLD = \033[1m


NAME 		= cub3d
CC			= cc
LIBFT		= lib/libft/libft.a
#CFLAGS		= -Wall -Werror -Wextra
CFLAGS		= -Wall -Werror -Wextra -g3
MLX_PATH = ./mlx_linux
LIBFT_PATH = ./lib/libft
VPATH		= ./srcs/:./srcs/RT:./srcs/parsing:./srcs/input_handling:./srcs/display:./srcs/utils:./lib/gnl:./srcs/RC
INC = -I/usr/include -Iincludes -Ilib/libft -Ilib/gnl

SRC_FILES	= main \
    parse parse2 display_handling textures keys\
	camera_rot movements\
	get_next_line get_next_line_utils\
    utils  exits\
	ray-casting\

OBJ_DIR = obj
OBJ	= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all: milix $(LIBFT) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(SEPIA)$(BOLD)Assembling YoRHa unit [$(NAME)]...$(RESET)"
	@$(CC) $(OBJ) $(INC) $(LIBFT) -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(WHITE)$(BOLD)▓ Unit $(NAME) ready for deployment. ▓$(RESET)"

$(LIBFT):
	@echo "$(SEPIA)$(BOLD)Initializing local libraries...$(RESET)"
	@make -s -C $(LIBFT_PATH)
	@echo "$(WHITE)Local libraries initialized.$(RESET)"

milix:
	@echo "$(SEPIA)$(BOLD)Initializing visual cortex...$(RESET)"
	@make -s -C $(MLX_PATH) > /dev/null
	@echo "$(WHITE)Visual cortex online.$(RESET)"

clean:
	@echo "$(SEPIA)Initiating cleanup protocol...$(RESET)"
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $@ -C $(MLX_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "$(WHITE)Memory banks cleared.$(RESET)"

fclean: clean
	@echo "$(SEPIA)Erasing all unit data...$(RESET)"
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $< -C $(MLX_PATH)
	@rm -rf $(OBJ_DIR)
	@rm -f ${NAME}
	@echo "$(WHITE)Unit data wiped from system.$(RESET)"

push:
	@echo "$(SEPIA)$(BOLD)Uploading data to Bunker...$(RESET)"
	@git add .
	@echo -n "$(WHITE)Enter transmission message: $(RESET)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(SEPIA)Data successfully transmitted: '$$commit_message'$(RESET)"

re: fclean all

.PHONY: all clean fclean re push mlx
