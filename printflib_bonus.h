/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflib_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:38:55 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:43:39 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFLIB_BONUS_H
# define PRINTFLIB_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

# define SPEC "cspdiuxX%"

typedef struct t_variables{
	va_list	args;
	int		width;
	int		negative;
	int		plus;
	int		sign;
	int		z;
	int		number;
	int		zero;
	int		point;
	int		s;
	int		asterisk;
	int		space;
	int		pad;
	int		next_s;
	int		prueba;
	int		is_null;
	int		value_i;
}	t_vari;

t_vari	*init_select(t_vari *select);
t_vari	*reset_select(t_vari *select);
int		its_negative(int num, t_vari *select);
void	ft_point2_s(char *aux, int i, t_vari *select, int length);
int		ft_size_s(char *aux, int i, int length, t_vari *select);
void	wr_negative_null(t_vari *select, int size, char *str, int len);
void	wr_null(t_vari *select, int size, char *str, int len);
void	wr_point_neg_s(t_vari *select, char *str, int len, int x);
void	wr_point_pos_s(t_vari *select, char *str, int len, int x);
void	wr_size_len(t_vari *select, char *str, int len, int size);
void	wr_len(t_vari *select, char *str, int x);
void	write_s(t_vari *select, char *str, int len, int size);
void	ft_category_s(t_vari *select, char *aux, int length, int i);
int		ft_size_c(char *aux, int i, int length, t_vari *select);
void	ft_category_c(t_vari *select, char *aux, int length, int i);
int		ft_point_p_sp(char *aux, int length, t_vari *select, int size);
int		ft_point_sp(char *aux, int length, t_vari *select, int size);
int		ft_point_z(char *aux, int i, t_vari *select, int size);
int		ft_ast(char *aux, int length, t_vari *select, int size);
int		ft_nast_npoint(char *aux, int length, t_vari *select, int size);
int		ft_all_point_d(t_vari *select, char *aux, int i, int length);
int		ft_size_d(char *aux, int i, int length, t_vari *select);
void	ft_check_sign(t_vari *select);
char	*ft_value_u(t_vari *select);
char	*ft_value_d(t_vari *select);
void	ft_s_neg_point(t_vari *select, int size, char *inter);
void	ft_s_neg(t_vari *select, int size, char *inter);
int		ft_zero_len(t_vari *select, int size, char *inter);
int		ft_len_zero(t_vari *select, int size, char *inter, char fill);
int		ft_neg_point_check(t_vari *select, int size, char *inter);
void	ft_point(t_vari *select, int size, char *inter);
void	ft_z_check(t_vari *select, int size, char *inter);
void	ft_nosize_d(t_vari *select, char *inter, int size);
void	ft_size_len_d(t_vari *select, char *inter, int size);
void	ft_category_d(t_vari *select, char *aux, int length, int i);
int		ft_size_p(char *aux, int i, int length, t_vari *select);
int		ft_numerlen(unsigned long long number);
char	*ft_p_hexa(char *inter, char *aux, int x, t_vari *select);
char	*ft_value_p(char *aux, int x, t_vari *select);
void	ft_size_len_p(t_vari *select, int size, char *inter);
void	ft_category_p(t_vari *select, char *aux, int length, int i);
void	ft_size_percent(t_vari *select, char c, char fill, int size);
void	ft_category_percent(t_vari *select, char *aux, int length, int i);
void	ft_checker(char *aux, int i, t_vari *select);
int		ft_percent(char *aux, int i, t_vari *select);
int		myprintf(char *aux, t_vari *select);
int		ft_printf(const char *input, ...);

#endif