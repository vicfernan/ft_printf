# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 19:55:57 by vifernan          #+#    #+#              #
#    Updated: 2021/08/19 17:50:24 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall -Werror -Wextra

SRCS	= 	ft_printf.c \
			ft_percent.c \
			ft_category_p.c	\
			ft_size_p.c	\
			ft_category_c.c	\
			ft_category_d.c	\
			ft_category_s.c	\
			ft_write_s_1.c \
			ft_write_s_2.c \
			ft_write_nosize.c \
			ft_write_size.c	\
			ft_size_d.c	\
			ft_on_off.c	\
			ft_checker.c \

BONUS_SRCS	=	ft_printf_bonus.c \
				ft_percent_bonus.c \
				ft_category_p_bonus.c \
				ft_size_p_bonus.c \
				ft_category_c_bonus.c \
				ft_category_d_bonus.c \
				ft_category_s_bonus.c \
				ft_write_s_1_bonus.c \
				ft_write_s_2_bonus.c \
				ft_write_nosize_bonus.c \
				ft_write_size_bonus.c \
				ft_size_d_bonus.c \
				ft_on_off_bonus.c \
				ft_checker_bonus.c \

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS_SRCS:.c=.o)

INCLUDES = -I./includes

all: $(NAME)

BCyan = \033[1;36m 
GREEN = \033[0;32m
Yellow = \033[0;33m
Red = \033[0;31m
NO_COLOR = \033[0m

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cp libft/libft.a $(NAME)
	@gcc -c $(CFLAGS) $(HEADER) $(SRCS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)[COMPILED]$(NO_COLOR)"

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	$(MAKE) fclean -C ./libft
	@echo "$(Yellow)[CLEAN]$(NO_COLOR)"

fclean: clean
	rm -rf $(NAME)
	@echo "$(Red)[FCLEAN]$(NO_COLOR)"
	
re: fclean all

bonus: $(OBJS_BONUS)
	@$(MAKE) -C ./libft
	@cp libft/libft.a $(NAME)
	@gcc -c $(CFLAGS) $(INCLUDES) $(BONUS_SRCS)
	@ar -rcs $(NAME) $(OBJS_BONUS)
	@echo "$(GREEN)[BONUS COMPILED]$(NO_COLOR)"

test: all
	@gcc $(CFLAGS) $(SRCS) $(NAME)
	@echo "$(BCyan)[RESULTS]$(NO_COLOR)"
	@./a.out | cat -e

.PHONY: all clean fclean re bonus test
