/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:39:30 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/15 16:24:52 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_LIB_H
# define PRINTF_LIB_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"
# define SPEC "cspdiuxX%"

typedef struct variables{
	va_list args;
	int width;
    int	negative;
    int	plus;
	int sign;
	int z;
	int number;
	int	zero;
	int	point;
	int s;
	int	asterisk;
	int	space;
	int	pad;
	int next_s;
	int prueba;
	int is_null;
} vari;

int ft_printf(const char *, ...);

#endif
