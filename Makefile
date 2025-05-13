NAME 		= cub3d
CC			= cc
LIB		= srcs/libft/libft.a
MLX		= mlx_linux/Makefile.gen
CFLAGS		= -Wall -Werror -Wextra
MLX_PATH = ./lib/mlx_linux/
VPATH		= ./srcs/:./srcs/RT
INC = -Iincludes/

SRC_FILES	=

OBJ	= $(addsuffix .o, $(SRC_FILES))

all: $(milix) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O2 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB) $(PTF) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imwlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(milix):
	@make -s -C $(MLX_PATH)

clean:
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $@ -C $(PRINTF_PATH)
	@make -s $@ -C $(MLX_PATH)
	rm -f ${OBJ} 

fclean: clean
	@make -s $@ -C $(LIBFT_PATH)
	@make -s $@ -C $(PRINTF_PATH)
	@make -s $@ -C $(MLX_PATH)
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re