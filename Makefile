# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 19:55:57 by vifernan          #+#    #+#              #
#    Updated: 2021/08/14 15:02:16 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall

SRCS	= ft_printf.c \

OBJS	= $(SRCS:.c=.o)

INCLUDES = -I./includes

all: $(NAME)

BCyan = \033[1;36m 
GREEN = \033[0;32m
Yellow = \033[0;33m
Red =" \033[0;31m
NO_COLOR = \033[0m

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cp libft/libft.a $(NAME)
	@gcc -c $(CFLAGS) $(INCLUDES) $(SRCS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓$(NO_COLOR)"

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(NAME)
	rm -rf $(OBJS)

fclean:
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

test: all
	@gcc $(FLAGS) ft_printf.c $(NAME)
	@echo "$(BCyan)[EJECUTADO]$(NO_COLOR)"
	@./a.out | cat -e

.PHONY: all clean fclean re bonus
