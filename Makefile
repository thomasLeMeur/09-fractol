# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 15:29:40 by tle-meur          #+#    #+#              #
#    Updated: 2016/02/03 18:28:53 by tle-meur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

FLAGS	=	-Wall -Wextra -Werror

SRCS	=	main.c parse.c utilities.c functions.c fractols.c init.c

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:
			@make -C libft/ simple
			@echo "libft.a created"
			@gcc $(FLAGS) -c $(SRCS) -I minilibx_macos/
			@gcc $(FLAGS) -o $(NAME) $(OBJS) -L libft/ -lft \
				-L /usr/lib/X11 -lX11 -lXext -L /usr/lib -lmlx
			@echo "fractol created"
clean	:
			@rm -f $(OBJS)
			@echo "objects deleted"

fclean	:	clean
			@rm -f $(NAME) libft/libft.a
			@echo "fractol and libft.a deleted"

re		:	fclean $(NAME)

simple	:	re
			@rm -f $(OBJS)
			@echo "objects deleted"

.PHONY	:	all clean fclean re simple
