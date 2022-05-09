# Program name
NAME	= cub3d
NAME^^	= $(shell echo $(NAME) | tr 'a-z' 'A-Z')

# Directories

INC_DIR	= include/
SRC_DIR	= srcs/
OBJ_DIR	= objs/

# Sources
__SRCS	= $(shell find $(SRC_DIR) -type f -name "*.c" | cut -c 6-)

SRCS	= $(addprefix $(SRC_DIR), $(__SRCS))
OBJS	= $(addprefix $(OBJ_DIR), $(__SRCS:.c=.o))

# Compile
CC		= clang

CFLAGS	= -Wall -Werror -Wextra -march=native #-g3 -fsanitize=address #-ggdb3 #-O3
INCLUDE	= -I $(INC_DIR) -I ./mlx -I ./libft
LIBS	= -L ./libft -lft -L ./mlx -lmlx -framework OpenGL -framework AppKit

# Format

OFFSET		= 25
OFFSET_OBJ	= 60

RESET		= \033[0;0m
FG_BWHIT	= \033[1;97m
FG_WHIT		= \033[0;97m
FG_BGRAY	= \033[1;37m
FG_GRAY		= \033[0;37m
FG_BMAGE	= \033[1;35m
FG_MAGE		= \033[0;35m
FG_BCYAN	= \033[1;36m
FG_CYAN		= \033[0;36m
FG_BGREE	= \033[1;32m
FG_GREE		= \033[0;32m

# Rules
all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(NAME).h
	mkdir -p $(OBJ_DIR)
	printf "$(FG_BGRAY)[ $(NAME^^) ] $(FG_BCYAN)OBJ\033[$(OFFSET)G$(FG_BWHIT): $(FG_WHIT)$@ $(FG_BCYAN)\033[$(OFFSET_OBJ)G[.]$(RESET)\r"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	printf "$(FG_BGRAY)[ $(NAME^^) ] $(FG_BCYAN)OBJ\033[$(OFFSET)G$(FG_BWHIT): $(FG_WHIT)$@ $(FG_BGREE)\033[$(OFFSET_OBJ)G[✓]$(RESET)\n"

$(NAME): $(OBJS)
	make -C ./libft
	make -s -C ./mlx
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) $(LIBS)
	printf "$(FG_BGRAY)[ $(NAME^^) ] $(FG_BGREE)BUILD\033[$(OFFSET)G$(FG_BWHIT): $(FG_BWHIT)$(NAME)$(RESET)\n"

clean:
	make -C ./libft clean
	make -s -C ./mlx clean
	rm -rf $(OBJ_DIR)
	printf "$(FG_BGRAY)[ $(NAME^^) ] $(FG_BMAGE)CLEAN\033[$(OFFSET)G$(FG_BWHIT): $(FG_WHIT).o files cleaned$(RESET)\n"

fclean: clean
	make -C ./libft fclean
	make -s -C ./mlx clean
	rm -f $(NAME)
	printf "$(FG_BGRAY)[ $(NAME^^) ] $(FG_BMAGE)FCLEAN\033[$(OFFSET)G$(FG_BWHIT): $(FG_WHIT)executable cleaned$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
.SILENT: