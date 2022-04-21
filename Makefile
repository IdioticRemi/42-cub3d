NAME		=	cub3d

INC			=	include
SRC_DIR		=	srcs
OBJ_DIR		=	objs

SRC			=	main.c				\
				display.c			\
				error.c				\
				exit.c				\
				fov.c				\
				free.c				\
				get_next_line.c		\
				init_game.c			\
				init_struct.c		\
				key_event.c			\
				map_check_old.c		\
				map_color_info.c	\
				map_read_old.c		\
				player_position.c	\
				vector_utils.c		\
				raycaster.c			\
				render.c			\

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

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c libft/libft.h include/cub3d.h
	$(CC) $(CFLAGS) -c $< -Iinclude -Ilibft -o $@ 

$(NAME):	init $(OBJS) $(LIBFT_FILE)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -I $(INC) $(LIBFT_FILE) -o $(NAME)

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
