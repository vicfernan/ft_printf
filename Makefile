# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 19:55:57 by vifernan          #+#    #+#              #
#    Updated: 2021/08/18 19:01:24 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall

SRCS	= 	ft_printf.c \
			ft_percent.c \
			ft_category_p.c	\
			ft_size_p.c	\
			ft_category_c.c	\
			ft_category_d.c	\
			ft_category_s.c	\
			ft_write_s_1.c	\
			ft_write_s_2.c	\
			ft_write_nosize.c	\
			ft_write_size.c	\
			ft_size_d.c	\
			ft_on_off.c	\
			ft_checker.c	\


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
	@gcc $(FLAGS) $(SRCS) $(NAME)
	@echo "$(BCyan)[EJECUTADO]$(NO_COLOR)"
	@./a.out | cat -e

.PHONY: all clean fclean re bonus
