SEPIA = \033[38;5;180m
BLACK = \033[0;30m
WHITE = \033[1;37m
GRAY = \033[0;37m
RESET = \033[0m
BOLD = \033[1m


NAME 		= cub3d
CC			= cc
LIB		= lib/libft/libft.a
MLX		= mlx_linux/Makefile.gen
CFLAGS		= -Wall -Werror -Wextra
MLX_PATH = ./lib/mlx_linux/
LIBFT_PATH = ./lib/libft
VPATH		= ./srcs/:./srcs/RT:./srcs/parsing:./srcs/input_handling:./srcs/display:./srcs/utils
INC = -Iincludes

SRC_FILES	= main \
	parse parse2 keys display_handling\
	utils \

OBJ	= $(addsuffix .o, $(SRC_FILES))

all: $(milix) $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(LIBFT) -I/usr/include -Imlx_linux -O2 -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(SEPIA)$(BOLD)Assembling YoRHa unit [$(NAME)]...$(RESET)"
	$(CC) $(OBJ) $(LIBFT) $(PTF) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(WHITE)$(BOLD)▓ Unit $(NAME) ready for deployment. ▓$(RESET)"

$(LIBFT):
	@echo "$(SEPIA)$(BOLD)Initializing local libraries...$(RESET)"
	@make -s -C $(LIB)
	@echo "$(WHITE)Local libraries initialized.$(RESET)"

$(milix):
	@echo "$(SEPIA)$(BOLD)Initializing visual cortex...$(RESET)"
	@make -s -C $(MLX_PATH)
	@echo "$(WHITE)Visual processing online.$(RESET)"

clean:
	@echo "$(SEPIA)Initiating cleanup protocol...$(RESET)"
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $@ -C $(MLX_PATH)
	rm -f ${OBJ} 
	@echo "$(WHITE)Memory banks cleared.$(RESET)"

fclean: clean
	@echo "$(SEPIA)Erasing all unit data...$(RESET)"
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $< -C $(MLX_PATH)
	rm -f ${NAME}
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

.PHONY: all clean fclean re push