NAME		=	cub3d

INC			=	include
SRC_DIR		=	srcs
OBJ_DIR		=	objs

SRC			=	error.c			\
				main.c			\
				get_next_line.c	\
				init_game.c		\
				map_check.c		\

SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

LIBFT		=	libft
LIBFT_FILE	=	$(LIBFT)/libft.a
MLX			=	mlx
RM			=	rm -rf

CC			=	gcc
CFLAGS		=	-g -D DEBUG -Wall -Wextra -Werror
CLIB		=	-I ./mlx -L ./mlx -lmlx -framework OpenGL -framework AppKit

all:	$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(LIBFT)/libft.h $(INC)/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -Ilibft
	# -c $< -Ilibft -o $@

# $(NAME):	init $(OBJS) $(LIBFT_FILE) 
# 	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -I $(INC) $(LIBFT_FILE) -o $(NAME)

$(NAME):	init ${OBJS} include/cub3d.h | libft/libft.a | mlx/mlx.h
			${GCCF} ${CLIB} $(OBJS) $(LIBFT_FILE) -o $(NAME)

init:
	@ mkdir -p objs
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MLX)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT) clean
	@ $(RM) objs
	rm -rf $(OBJS) 

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(MLX) clean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re init re_lib
