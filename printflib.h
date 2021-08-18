/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:39:30 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 20:03:17 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFLIB_H
# define PRINTFLIB_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

# define SPEC "cspdiuxX%"

typedef struct variables{
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
}	t_vari;

vari	*init_select(vari *select);
vari	*reset_select(vari *select);
int		its_negative(int num, vari *select);
void	ft_point2_s(char *aux, int i, vari *select, int length, int size);
int		ft_size_s(char *aux, int i, int length, vari *select);
void	wr_null(vari *select, int size, char *str, int len, int x);
void	wr_point_neg_s(vari *select, char *str, int len, int x);
void	wr_point_pos_s(vari *select, char *str, int len, int x);
void	wr_size_len(vari *select, char *str, int len, int x, int size);
void	wr_len(vari *select, char *str, int len, int x);
void	write_s(vari *select, char *str, int len, int size);
void	ft_category_s(vari *select, char *aux, int length, int i);
int		ft_size_c(char *aux, int i, int length, vari *select);
void	ft_category_c(vari *select, char *aux, int length, int i);
int		ft_point_p_sp(char *aux, int i, int length, vari *select, int size);
int		ft_point_sp(char *aux, int i, int length, vari *select, int size);
int		ft_point_z(char *aux, int i, vari *select, int size);
int		ft_ast(char *aux, int i, int length, vari *select, int size);
int		ft_nast_npoint(char *aux, int i, int length, vari *select, int size);
int		ft_all_point_d(vari *select, char *aux, int i, int length);
int		ft_size_d(char *aux, int i, int length, vari *select);
void	ft_check_sign(vari *select);
char	*ft_value_u(vari *select);
char	*ft_value_d(vari *select);
void	ft_s_neg_point(vari *select, int size, char *inter);
void	ft_s_neg(vari *select, int size, char *inter);
int		ft_zero_len(vari *select, int size, char *inter);
int		ft_len_zero(vari *select, int size, char *inter, char fill);
int		ft_neg_point_check(vari *select, int size, char *inter);
void	ft_point(vari *select, int size, char *inter);
void	ft_z_check(vari *select, int size, char *inter);
void	ft_nosize_d(vari *select, char *inter, int size);
void	ft_size_len_d(vari *select, char *inter, int size);
void	ft_category_d(vari *select, char *aux, int length, int i);
int		ft_size_p(char *aux, int i, int length, vari *select);
int		ft_numerlen(unsigned long long number);
char	*ft_p_hexa(char *inter, char *aux, int x, vari *select);
char	*ft_value_p(char *aux, int x, vari *select);
void	ft_size_len_p(vari *select, int size, char *inter);
void	ft_category_p(vari *select, char *aux, int length, int i);
void	ft_size_percent(vari *select, char c, char fill, int size);
void	ft_category_percent(vari *select, char *aux, int length, int i);
void	ft_checker(char *aux, int i, vari *select);
int		ft_percent(char *aux, int i, vari *select);
int		myprintf(char *aux, va_list args, vari *select);
int		ft_printf(const char *input, ...);

#endif
