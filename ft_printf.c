/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/15 19:52:04 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

vari	*init_select(vari *select)
{
	select->width = 0;
	select->zero = 0;
	select->space = 0;
	select->point = 0;
	select->sign = 0;
	select->plus = 0;
	select->pad = 0;
	select->z = 0;
	select->s = 0;
	select->number = 0;
	select->negative = 0;
	select->asterisk = 0;
	select->is_null = 0;
	select->prueba = 0;

	return (select);
}

vari	*reset_select(vari *select)
{
	select->zero = 0;
	select->space = 0;
	select->point = 0;
	select->sign = 0;
	select->number = 0;
	select->plus = 0;
	select->s = 0;
	select->pad = 0;
	select->z = 0;
	select->negative = 0;
	select->asterisk = 0;
	select->is_null = 0;
	select->prueba = 0;

	return (select);
}

/*---START -C- <---*/

int		its_negative(int num, vari *select)
{
	if (num < 0)
	{
		num *= -1;
		select->negative++;
	}
	return (num);
}

void	ft_point2_s(char *aux, int i, vari *select, int length, int size)
{
	char *temp;

	temp = ft_substr(aux, i - length, length - (i - select->point));
	if (ft_strchr(temp, '*') > 0)
		select->pad = va_arg(select->args, int);
	else
		select->pad = ft_atoi(temp);
	free(temp);
	size = its_negative(size, select);
	temp = ft_substr(aux, select->point + 1, (i - select->point) - 1);
	if (ft_strchr(temp, '*') > 0)
		select->space = va_arg(select->args, int);
	else
		select->space = ft_atoi(temp);
	free(temp);
}

int	ft_size_s(char *aux, int i, int length, vari *select)
{
	int		size;
	char	*temp;

	size = 0;
	if (select->point > 0)
		ft_point2_s(aux, i, select, length, size);
	else if (select->asterisk == 0)
	{
		temp = ft_substr(aux, i - length, length);
		size = ft_atoi(temp);
		free(temp);
		size = its_negative(size, select);
	}
	else
	{
		size = va_arg(select->args, int);
		size = its_negative(size, select);
	}
	select->pad = its_negative(select->pad, select);
	return (size);
}
/*
if (str == NULL)
{
	if (size == 0 && select->pad == 0)
	{
		size = select->space;
		if (size < 0 || size > 6)
			size = 6;
	}
	str = "(null)";
	select->is_null++;
}
*/

void	wr_null(vari *select, int size, char *str, int len, int x)
{
	if (select->is_null > 0 && select->point > 0 && size == 0 && select->zero == 0)
			size = 0;
	else if (select->space <= 0 && select->pad <= 0 && select->point > 0)
	{
		while (x < (int)ft_strlen(str))
			select->width += write(1, &str[x++], 1);
	}
	else if (select->negative > 0)
	{
		while (x < len)
		{
			select->width += write(1, &str[x++], 1);
			size--;
		}
		while (size-- > 0)
			select->width += write(1, " ", 1);
	}
	else
	{
		while (size-- > len)
			select->width += write(1, " ", 1);
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
}

void	wr_point_neg_s(vari *select, char *str, int len, int x)
{
	if (select->pad > len)
	{
		while (len-- > 0 && select->pad--)
			select->width += write(1, &str[x++], 1);
		while (select->pad-- > 0)
			select->width += write(1, " ", 1);
	}
	else
	{
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
}

void	wr_point_pos_s(vari *select, char *str, int len, int x)
{
	if (select->pad > len)
	{
		while (select->pad-- > len)
			select->width += write(1, " ", 1);
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
	else if (select->space == 0 && select->pad == 0)
		select->point++;
	else
	{
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
}

void	wr_size_len(vari *select, char *str, int len, int x, int size)
{
	if (select->negative > 0)
	{
		while (len-- > 0 && size--)
			select->width += write(1, &str[x++], 1);
		while (size-- > 0)
			select->width += write(1, " ", 1);
	}
	else
	{
		while (size-- > len)
			select->width += write(1, " ", 1);
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
}

void	wr_len(vari *select, char *str, int len, int x)
{
	if (select->space > 0)
	{
		while (select->space-- > 0)
			select->width += write(1, &str[x++], 1);
	}
	else
	{
		while (x < (int)ft_strlen(str))
			select->width += write(1, &str[x++], 1);
	}
}

void	write_s(vari *select, char *str, int len, int size)
{
	int x;

	x = 0;
	if (select->is_null > 0)
	{
		if (select->pad > size)
			size = select->pad;
		wr_null(select, size, str, len, x);
	}
	else if (select->point > 0)
	{
		if (select->negative > 0)
			wr_point_neg_s(select, str, len, x);
		else
			wr_point_pos_s(select, str, len, x);
	}
	else if (size > len)
		wr_size_len(select, str, len, x, size);
	else
		wr_len(select, str, len, x);
}

void	ft_category_s(vari *select, char *aux, int length, int i)
{
	char 	*str;
	int		size;
	int		len;

	size = ft_size_s(aux, i, length, select);
	str = va_arg(select->args, char *);
	if (str == NULL)
	{
		if (size == 0 && select->pad == 0)
		{
			size = select->space;
			if (size < 0 || size > 6)
				size = 6;
		}
		str = "(null)";
		select->is_null++;
	}
	len = (int)ft_strlen(str);
	if ((len > select->space && select->space >= 0) && select->point > 0)
		len = select->space;
	write_s(select, str, len, size);
}

int	ft_size_c(char *aux, int i, int length, vari *select)
{
	int		size;
	char	*temp;

	if (select->asterisk == 0)
	{
		temp = ft_substr(aux, i - length, length);
		size = ft_atoi(temp);
		free(temp);
		if (size < 0)
			size *= -1;
	}
	else
	{
		size = va_arg(select->args, int);
		if (size < 0)
		{
			size *= -1;
			select->negative++;
		}
	}
	return (size);
}

void	ft_category_c(vari *select, char *aux, int length, int i)
{
	char 	c;
	int		size;

	size = ft_size_c(aux, i, length, select);
	c = va_arg(select->args, int);
	if (size > 0)
	{
		if (select->negative > 0)
		{
			select->width += write(1, &c, 1);
			while (size-- > 1)
				select->width += write(1, " ", 1);
		}
		else
		{
			while (size-- > 1)
				select->width += write(1, " ", 1);
			select->width += write(1, &c, 1);
		}
	}
	else
		select->width += write(1, &c, 1);
}
/*---end -c- <---*/

/*---START > D <---*/

/*--- start size d ---*/
int	ft_point_p_sp(char *aux, int i, int length, vari *select, int size)
{
	char *temp;

	temp = ft_substr(aux, i - (length - 1), (length - 1) - (i - select->point));
	if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
		select->space = va_arg(select->args, int);
	else
		select->space = ft_atoi(temp);
	if (select->space < 0)
		select->space *= -1;
	free(temp);
	return (select->space);
}

int	ft_point_sp(char *aux, int i, int length, vari *select, int size)
{
	char *temp;

	temp = ft_substr(aux, i - length, length - (i - select->point));
	if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
		select->space = va_arg(select->args, int);
	else
	{
		if (temp[0] == '0')
			temp[0] = ' ';
		select->space = ft_atoi(temp);
	}
	if (select->space < 0)
	{
		select->space *= -1;
		select->negative++;
	}
	free(temp);
	return (select->space);
}

int	ft_point_z(char *aux, int i, vari *select, int size)
{
	char *temp;

	temp = ft_substr(aux, select->point + 1, (i - select->point) - 1);
	if (temp[size] == '*' && select->asterisk--)
		select->zero = va_arg(select->args, int);
	else
		select->zero = ft_atoi(temp);
	if (select->zero < 0)
	{
		select->zero *= -1;
		if (select->zero > select->space)
		{
			select->negative++;
		}
		else
			select->prueba++;
		select->pad++;
	}
	free(temp);
	return (select->zero);
}

int	ft_ast(char *aux, int i, int length, vari *select, int size)
{
	char *temp;

	temp = ft_substr(aux, i - length, length);
	if (temp[0] == '0' || temp[1] == '0')
		select->z++;
	free(temp);
	size = va_arg(select->args, int);
	if (size < 0)
	{
		size *= -1;
		select->negative++;
	}
	return (size);
}

int ft_nast_npoint(char *aux, int i, int length, vari *select, int size)
{
	char *temp;
	
	if (select->plus > 0)
	{
		temp = ft_substr(aux, select->plus + 1, (i - select->plus + 1));
		if (temp[1] == '0')
			select->z++;
		size = ft_atoi(temp);
		free(temp);
		if (size < 0 && select->negative++)
			size *= -1;
	}
	else
	{
		temp = ft_substr(aux, i - length, length);
		if (temp[1] == '0')
			select->z++;
		size = ft_atoi(temp);
		free(temp);
		if (size < 0)
			size *= -1;
	}
	return (size);
}

int	ft_all_point_d(vari *select, char *aux, int i, int length)
{
	int size;

	size = 0;
	if (select->plus > 0)
		select->space = ft_point_p_sp(aux, i, length, select, size);
	else
		select->space = ft_point_sp(aux, i, length, select, size);
	select->zero = ft_point_z(aux, i, select, size);
	if (select->space >= select->zero)
		size = select->space;
	else
	{
		size = select->zero;
		select->next_s++;
	}
	return (size);
}

int	ft_size_d(char *aux, int i, int length, vari *select)
{
	int		size;
	char	*temp;

	size = 0;
	temp = ft_substr(aux, i - length, length);
	if (temp[0] == '0')
		select->z++;
	if (temp[0] == ' ')
		select->s++;
	free(temp);
	if (select->point > 0)
		size = ft_all_point_d(select, aux, i, length);
	if (select->asterisk > 0 && select->point == 0)
		size = ft_ast(aux, i, length, select, size);
	if (select->asterisk == 0 && select->point == 0)
		size = ft_nast_npoint(aux, i, length, select, size);
	return (size);
}
/*--- end size d ---*/

/*--- start print d ---*/

void	ft_check_sign(vari *select)
{
	if (select->sign > 0)
		select->width += write(1, "-", 1);
	else
		select->width += write(1, "+", 1);
}


char	*ft_value_u(vari *select)
{
	unsigned int	number;
	char			*inter;

	number = (unsigned int)va_arg(select->args, int);
	if (number == 0)
		select->number++;
	if (number < 0 && (int)number != INT_MIN)
	{
		select->plus++;
		select->sign++;
		number *= -1;
	}
	inter = ft_itoa(number);
	if (select->number > 0 && select->space > 0 && select->zero == 0)
		inter[0] = ' ';
	return (inter);
}

char	*ft_value_d(vari *select)
{
	int		number;
	char	*inter;

	number = va_arg(select->args, int);
	if (number == 0)
		select->number++;
	if (number < 0 && number != INT_MIN)
	{
		select->plus++;
		select->sign++;
		number *= -1;
	}
	inter = ft_itoa(number);
	if (select->number > 0 && select->space > 0 && select->zero == 0)
		inter[0] = ' ';
	return (inter);
}

void	ft_s_neg_point(vari *select, int size, char *inter)
{
	int i;

	i = 0;
	if (select->zero >= select->space && select->plus > 0)
		size++;
	if (select->plus > 0 && size--)
		ft_check_sign(select);
	if (select->pad > 0)
	{
		if (select->zero > select->space)
		{
			while (select->zero-- > (int)ft_strlen(inter))
				size--;
		}
	}
	else
	{
		while (select->zero-- > (int)ft_strlen(inter) && size--)
			select->width += write(1, "0", 1);
	}
	while (inter[i] != '\0' && size--)
		select->width += write(1, &inter[i++], 1);
	while (size-- > 0)
		select->width += write(1, " ", 1);
}

void	ft_s_neg(vari *select, int size, char *inter)
{
	int i;

	i = 0;
	if (select->sign > 0 && size--)
		ft_check_sign(select);
	while (inter[i] != '\0' && size--)
		select->width += write(1, &inter[i++], 1);
	while (size-- > 0)
		select->width += write(1, " ", 1);
}

int	ft_zero_len(vari *select, int size, char *inter)
{
	if (select->s > 0)
		size--;
	while (select->space-- > select->zero && size--)
	{
		select->width += write(1, " ", 1);
	}
	if (select->plus > 0 && size--)
		ft_check_sign(select);
	while (select->zero-- > (int)ft_strlen(inter) && size--)
		select->width += write(1, "0", 1);

	return (size);
}

int	ft_len_zero(vari *select, int size, char *inter, char fill)
{
	if (size > (int)ft_strlen(inter) && select->z > 0 && select->point > 0 && select->prueba > 0)
	{
		if (select->plus > 0 && size--) 
			ft_check_sign(select);
		while (select->space-- > (int)ft_strlen(inter) && size--)
			select->width += write(1, &fill, 1);
	}
	else
	{
		while (select->space-- > (int)ft_strlen(inter) && size--)
			select->width += write(1, &fill, 1);
		if (select->plus > 0 && size--)
			ft_check_sign(select);
	}

	return (size);
}
int	ft_neg_point_check(vari *select, int size, char *inter)
{
	char fill;

	if (select->z > 0 && select->point > 0 && select->prueba > 0)
		fill = '0';
	else
		fill = ' ';
	if (select->zero > (int)ft_strlen(inter) && select->prueba == 0) 
		size = ft_zero_len(select, size, inter);
	else
		size = ft_len_zero(select, size, inter, fill);
	return (size);
}

void	ft_point(vari *select, int size, char *inter)
{
	int i;

	i = 0;
	if (select->space <= select->zero && select->plus > 0)
		size++;
	if (select->space > select->zero && select->plus > 0)
		select->space--;
	size = ft_neg_point_check(select, size, inter);
	if (select->next_s > 0)
	{
		while (inter[i] != '\0')
			select->width += write(1, &inter[i++], 1);
	}
	else
	{
		while (inter[i] != '\0' && size--)
			select->width += write(1, &inter[i++], 1);
		while (size-- > 0)
			select->width += write(1, "0", 1);
	}
}

void	ft_z_check(vari *select, int size, char *inter)
{
	int i;

	i = 0;
	if (select->z > 0)
	{
		if (select->plus > 0 || select->sign > 0)
			size--;
		if ((select->plus > 0 || select->sign > 0))
			ft_check_sign(select);
		while (size-- > (int)ft_strlen(inter))
			select->width += write(1, "0", 1);
		while (inter[i] != '\0')
			select->width += write(1, &inter[i++], 1);
	}
	else
	{
		if (select->plus > 0 || select->sign > 0)
			size--;
		while (size-- > (int)ft_strlen(inter))
			select->width += write(1, " ", 1);
		if ((select->plus > 0 || select->sign > 0))
			ft_check_sign(select);
		while (inter[i] != '\0')
			select->width += write(1, &inter[i++], 1);
	}
}

void	ft_nosize_d(vari *select, char *inter, int size)
{
	int i;

	i = 0;
	if (size == 0 && inter[i] == '0' && select->point == 0 && select->prueba == 0)
		select->width += write(1, "0", 1);
	else if (select->number > 0 && size == 0 && (select->point > 0 || select->asterisk > 0))
		select->number++;
	else
	{
		if (select->plus > 0)
			ft_check_sign(select);
		while (inter[i] != '\0')
			select->width += write(1, &inter[i++], 1);
	}
}

void	ft_size_len_d(vari *select, char *inter, int size)
{
	if (select->negative > 0)
	{
		if (select->point > 0)
			ft_s_neg_point(select, size, inter);
		else
			ft_s_neg(select, size, inter);
	}
	else
	{
		if (select->s > 0 && size--)
			select->width += write(1, " ", 1);
		if (select->point > 0)
			ft_point(select, size, inter);
		else
			ft_z_check(select, size, inter);
	}
}

void	ft_category_d(vari *select, char *aux, int length, int i)
{
	char	*inter;
	int		size;
	
	size = ft_size_d(aux, i, length, select);
	if (aux[i] == 'u')
		inter = ft_value_u(select);
	else
		inter = ft_value_d(select);
	if (size > (int)ft_strlen(inter))
		ft_size_len_d(select, inter, size);
	else
		ft_nosize_d(select, inter, size);
	free(inter);
}

/*--- end print d ---*/

/*---START P---*/


int	ft_size_p(char *aux, int i, int length, vari *select)
{
	int		size;

	size = 0;
	if (aux[1] == '0')
		select->z++;
	if (select->point > 0)
	{
		if (select->plus > 0)
			select->space = ft_point_p_sp(aux, i, length, select, size);
		else
			select->space = ft_point_sp(aux, i, length, select, size);
		select->zero = ft_point_z(aux, i, select, size);
		if (select->space > select->zero)
			size = select->space;
		else
			size = select->zero;
	}
	if (select->asterisk > 0 && select->point == 0)
		size = ft_ast(aux, i, length, select, size);
	if (select->asterisk == 0 && select->point == 0)
		size = ft_nast_npoint(aux, i, length, select, size);
	return (size);
}

int		ft_numerlen(unsigned long long number)
{
	int i;

	i = 0;
	while (number >= 16)
	{
		number /= 16;
		i++;
	}
	i++;
	return (i);
}

char	*ft_p_hexa(char *inter, char *aux, int x, vari *select)
{
	char	*hexa_g;
	int		i;
	int		j;

	i = (int)ft_strlen(inter);
	if (aux[x] == 'p')
	{
		hexa_g = malloc((i + 3) * sizeof(char));
		select->prueba++;
		hexa_g[0] = '0';
		hexa_g[1] = 'x';
		j = 2;
	}
	else
	{
		hexa_g = malloc(i + 1 * sizeof(char));
		j = 0;
	}
	while (--i >= 0)
		hexa_g[j++] = inter[i];
	hexa_g[j] = '\0';
	free(inter);
	return (hexa_g);
}

char	*ft_value_p(char *aux, int x, vari *select)
{
	unsigned long long		number;
	char					*inter;
	char					*hexa;
	int						i;

	if (aux[x] == 'X')
		hexa = "0123456789ABCDEF";
	else
		hexa = "0123456789abcdef";
	if (aux[x] == 'X' || aux[x] == 'x')
		number = (unsigned int) va_arg(select->args, void *);
	else
		number = (unsigned long long) va_arg(select->args, void *);
	if (number == 0)
		select->number++;
	inter = malloc(ft_numerlen(number) + 1 * sizeof(char));
	i = 0;
	while (number >= 16)
	{
		inter[i++] = hexa[number % 16];
		number = number / 16;
	}
	inter[i++] = hexa[number % 16];
	inter[i] = '\0';
	return (ft_p_hexa(inter, aux, x, select));
}

void	ft_size_len_p(vari *select, int size, char *inter)
{
	if (select->negative > 0)
	{
		if (select->point > 0)
			ft_s_neg_point(select, size, inter);
		else
			ft_s_neg(select, size, inter);
	}
	else
	{
		if (select->point > 0)
			ft_point(select, size, inter);	
		else
			ft_z_check(select, size, inter);
	}
}

void	ft_category_p(vari *select, char *aux, int length, int i)
{
	char	*inter;
	int		size;

	size = ft_size_p(aux, i, length, select);
	inter = ft_value_p(aux, i, select);
	if (select->number > 0 && select->space > 0 && select->zero == 0)
		inter[0] = ' ';
	if (aux[i] == 'p')
		select->z = 0;
	if (size > (int)ft_strlen(inter))
		ft_size_len_p(select, size, inter);
	else
		ft_nosize_d(select, inter, size);
	free(inter);
}

/*---end P---*/

/*---START -%- <---*/

void	ft_size_percent(vari *select, char c, char fill, int size)
{
	if (select->negative > 0)
	{
		select->width += write(1, &c, 1);
		while (size-- > 1)
			select->width += write(1, &fill, 1);
	}
	else
	{
		while (size-- > 1)
			select->width += write(1, &fill, 1);
		select->width += write(1, &c, 1);
	}
}
void	ft_category_percent(vari *select, char *aux, int length, int i)
{
	int		size;
	char	c;
	char	fill;
	char	*temp;

	fill = ' ';
	temp = ft_substr(aux, i - length, length);
	if (temp[0] == '0')
		fill = '0';
	free(temp);
	size = ft_size_d(aux, i, length, select);
	c = '%';
	if (size > 0)
		ft_size_percent(select, c, fill, size);
	else
		select->width += write(1, &c, 1);
}

/*--end -%- --*/

void	ft_checker(char *aux, int i, vari *select)
{
	if (aux[i] == '0')
		select->z++;
	if (aux[i] == '-')
		select->negative++;
	if (aux[i] == '*')
		select->asterisk++;
	if (aux[i] == '.')
		select->point = i;
	if (aux[i] == '+')
		select->plus = i;
}

int ft_percent(char *aux, int i, vari *select)
{
	int 		length;

	length = 0;
	while (!ft_strchr(SPEC, aux[++i]))
	{
		ft_checker(aux, i, select);
		length++;
	}
	if (aux[i] == 'c')
		ft_category_c(select, aux, length, i);
	if (aux[i] == 's')
		ft_category_s(select, aux, length, i);
	if (aux[i] == 'd' || aux[i] == 'i' || aux[i] == 'u')
		ft_category_d(select, aux, length, i);
	if (aux[i] == 'p' || aux[i] == 'x' || aux[i] == 'X')
		ft_category_p(select, aux, length, i);
	if (aux[i] == '%')
		ft_category_percent(select, aux, length, i);
	reset_select(select);
	return (++length);
}

int	myprintf(char *aux, va_list args, vari *select)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	while (aux[i] != '\0')
	{
		if (aux[i] != '%')
			select->width += write(1, &aux[i], 1);
		else
			i += ft_percent(aux, i, select);
		i++;
	}
	return (select->width);
}

int	ft_printf(const char *input, ...)
{
	vari	*select;
	int		count;
	char	*aux;

	select = (vari *)malloc(sizeof(vari));
	if (!select)
		return (-1);
	init_select(select);
	count = 0;
	aux = (char*)input;
	va_start(select->args, input);
	count = myprintf(aux, select->args, select);
	va_end(select->args);
	free(select);
	return (count);
}