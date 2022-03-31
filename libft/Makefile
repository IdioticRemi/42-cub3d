# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 13:48:53 by selee             #+#    #+#              #
#    Updated: 2021/08/07 23:06:44 by seoyounglee      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER	= libft.h

SRCS	= ft_bzero.c ft_calloc.c ft_isalnum.c\
		  ft_isalpha.c ft_isascii.c ft_isdigit.c\
		  ft_isprint.c ft_memccpy.c ft_memchr.c\
		  ft_memcmp.c ft_memcpy.c ft_memmove.c\
		  ft_memset.c ft_putchar_fd.c ft_putstr_fd.c\
		  ft_strchr.c ft_strdup.c ft_strjoin.c\
		  ft_strlcat.c ft_strlcpy.c ft_strlen.c\
		  ft_strncmp.c ft_strnstr.c ft_strrchr.c\
		  ft_substr.c ft_tolower.c ft_toupper.c\
		  ft_putendl_fd.c ft_putnbr_fd.c ft_atoi.c\
		  ft_itoa.c ft_strtrim.c ft_strmapi.c\
		  ft_split.c ft_itoa_base.c ft_utoa_base.c\
		  ft_strstr.c ft_strcmp.c ft_atoi_base.c\
		  ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c\
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
		  ft_lstiter.c ft_lstmap.c

OBJS	= $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

COMP		=	gcc

NAME	= libft.a

CFLAGS	= -g -Wall -Wextra -Werror

%.o: %.c $(HEADER)
	$(COMP) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	$(AR) rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) rs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean bonus
