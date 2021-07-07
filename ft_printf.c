/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/07/07 13:26:21 by vifernan         ###   ########.fr       */
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
	select->number = 0;
	select->negative = 0;
	select->asterisk = 0;

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
	select->pad = 0;
	select->z = 0;
	select->negative = 0;
	select->asterisk = 0;

	return (select);
}

int	ft_size_c(char *aux, int i, int length, vari *select, va_list args)
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
		size = va_arg(args, int);
		if (size < 0)
		{
			size *= -1;
			select->negative++;
		}
	}
	return (size);
}

void	ft_category_c(va_list args, vari *select, char *aux, int length, int i)
{
	char 	c;
	int		size;

	size = ft_size_c(aux, i, length, select, args);
	c = va_arg(args, int);
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

/*---ESTAMOS EN LA > D <---*/

int	ft_size_d(char *aux, int i, int length, vari *select, va_list args)
{
	int		size;
	char	*temp;

	size = 0;
	if (aux[1] == '0')
		select->z++;
	if (select->point > 0)
	{
		if (select->plus > 0)
		{
			temp = ft_substr(aux, i - (length - 1), (length - 1) - (i - select->point));
			if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
				select->space = va_arg(args, int);
			else
				select->space = ft_atoi(temp);
			if (select->space < 0)
				select->space *= -1;
			free(temp);
		}
		else
		{
			temp = ft_substr(aux, i - length, length - (i - select->point));
			if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
				select->space = va_arg(args, int);
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
		}
		temp = ft_substr(aux, select->point + 1, (i - select->point) - 1);
		if (temp[size] == '*' && select->asterisk--)
			select->zero = va_arg(args, int);
		else
			select->zero = ft_atoi(temp);
		if (select->zero < 0)
		{
			select->zero *= -1;
			select->negative++;
		}
		free(temp);
		if (select->space > select->zero)
			size = select->space;
		else
			size = select->zero;
	}
	/*kcjrbekhrc*/
	if (select->asterisk > 0 && select->point == 0)
	{
		temp = ft_substr(aux, i - length, length);
		if (temp[0] == '0' || temp[1] == '0')
			select->z++;
		free(temp);
		size = va_arg(args, int);
		if (size < 0)
		{
			size *= -1;
			select->negative++;
		}
	}
	if (select->asterisk == 0 && select->point == 0)
	{
		if (select->plus > 0)
		{
			temp = ft_substr(aux, select->plus + 1, (i - select->plus + 1));
			if (temp[1] == '0')
				select->z++;
			size = ft_atoi(temp);
			free(temp);
			if (size < 0)
			{
				size *= -1;
				select->negative++; /* check */ 
			}
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
	}
	return (size);
}

void	ft_category_d(va_list args, vari *select, char *aux, int length, int i)
{
	char	*inter;
	int		size;
	int		z;
	int		number;
	
	size = ft_size_d(aux, i, length, select, args);
	number = va_arg(args, int);
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
	z = 0;
	if (size > (int)ft_strlen(inter))
	{
		if (select->negative > 0)
		{
			if (select->point > 0)
			{
				if (select->zero >= select->space && select->plus > 0)
					size++;
				if (select->plus > 0 && size--)
				{
					if (select->sign > 0)
						select->width += write(1, "-", 1);
					else
						select->width += write(1, "+", 1);
				}
				while (select->zero-- > (int)ft_strlen(inter) && size--)
					select->width += write(1, "0", 1);
				while (inter[z] != '\0' && size--)
					select->width += write(1, &inter[z++], 1);
				while (size-- > 0)
					select->width += write(1, " ", 1);
			}
			else
			{
				if ((select->plus > 0 || select->sign > 0))
				{
					if (select->sign > 0)
						select->width += write(1, "-", 1);
					else
						select->width += write(1, "+", 1);
					size--;
				}
				while (inter[z] != '\0' && size--)
					select->width += write(1, &inter[z++], 1);
				while (size-- > 0)
					select->width += write(1, " ", 1);
			}
		}
		else
		{
			if (select->point > 0)
			{
				if (select->space <= select->zero && select->plus > 0)
					size++;
				if (select->space > select->zero && select->plus > 0)
					select->space--;
				if (select->zero > (int)ft_strlen(inter))
				{
					while (select->space-- > select->zero && size--)
						select->width += write(1, " ", 1);
					if (select->plus > 0 && size--)
					{
						if (select->sign > 0)
							select->width += write(1, "-", 1);
						else
							select->width += write(1, "+", 1);
					}
					while (select->zero-- > (int)ft_strlen(inter) && size--)
						select->width += write(1, "0", 1);
				}
				else
				{
					while (select->space-- > (int)ft_strlen(inter) && size--)
						select->width += write(1, " ", 1);
					if (select->plus > 0 && size--)
					{
						if (select->sign > 0)
						select->width += write(1, "-", 1);
					else
						select->width += write(1, "+", 1);
					}
				}
				while (inter[z] != '\0' && size--)
					select->width += write(1, &inter[z++], 1);
				while (size-- > 0)
					select->width += write(1, "0", 1);
			}
			else
			{
				if (select->z > 0)
				{
					if (select->plus > 0 || select->sign > 0)
						size--;
					if ((select->plus > 0 || select->sign > 0))
					{
						if (select->sign > 0)
							select->width += write(1, "-", 1);
						else
							select->width += write(1, "+", 1);
					}
					while (size-- > (int)ft_strlen(inter))
						select->width += write(1, "0", 1);
					while (inter[z] != '\0')
						select->width += write(1, &inter[z++], 1);
				}
				else
				{
					if (select->plus > 0 || select->sign > 0)
						size--;
					while (size-- > (int)ft_strlen(inter))
						select->width += write(1, " ", 1);
					if ((select->plus > 0 || select->sign > 0))
					{
						if (select->sign > 0)
							select->width += write(1, "-", 1);
						else
							select->width += write(1, "+", 1);
					}
					while (inter[z] != '\0')
						select->width += write(1, &inter[z++], 1);
				}
			}
		}
	}
	else if (select->number > 0 && size == 0 && (select->point > 0 || select->asterisk > 0))
		select->number++;
	else
	{
		if (select->plus > 0)
		{
			if (select->sign > 0)
				select->width += write(1, "-", 1);
			else
				select->width += write(1, "+", 1);
		}
		while (inter[z] != '\0')
			select->width += write(1, &inter[z++], 1);
	}
	free(inter);
}

/*---TERMINA AQUI---*/

int ft_percent(char *aux, int i, va_list args, vari *select)
{
	int 		length;

	length = 0;
	while (!ft_strchr(SPEC, aux[++i]))
	{
		if (aux[i] == '-')
			select->negative++;
		if (aux[i] == '*')
			select->asterisk++;
		if (aux[i] == '.')
			select->point = i;
		if (aux[i] == '+')
			select->plus = i;
		length++;
	}
	if (aux[i] == 'c')
		ft_category_c(args, select, aux, length, i);
	if (aux[i] == 'd' || aux[i] == 'i')
		ft_category_d(args, select, aux, length, i);
	reset_select(select);
	return (++length);
}

int	myprint(char *aux, va_list args, vari *select)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	while (aux[i] != '\0')
	{
		if (aux[i] == '%')
			i += ft_percent(aux, i, args, select);
		else
			select->width += write(1, &aux[i], 1);	
		i++;
	}
	return (select->width);
}

int	ft_printf(const char *input, ...)
{
	vari	*select;
	int count;
	char		*aux;

	select = (vari *)malloc(sizeof(vari));
	if (!select)
		return (-1);
	init_select(select);
	count = 0;
	aux = (char*)input;
	va_start(select->args, input);
	count = myprint(aux, select->args, select);
	va_end(select->args);
	free(select);
	return (count);
}
/*
int main()
{
	//int a = 23;
	//char b = 'i';
	//char c = 'c';
	//char d = 'V';
	//char e = '&';
	//long l = -8723647987432;
	//int count;
	//int count2;

	//ft_printf("*** %-10c hola %c%c%c %*c\n", 'c', d, b, c, 100, e);
	//printf("*** %-10c hola %c%c%c %*c\n", 'c', d, b, c, 100, e);
	//printf("*PRINTF* %d %i %zu %d %s %cictor          \n\n\n\n\n", a, b, l, c, e, d);
	//ft_printf("%1*0d\n", 400);
	//ft_printf("%*.*d\n", 5, 25, 400);
	//printf("%*.*d\n", 5, 25, 400);
	//ft_printf(" %100.d\n", 0);
	//printf(" %100.d\n", 0);
	//ft_printf(" %.d\n", 0);
	//printf(" %.d\n", 0);
	//prinf("%d", UINT_MAX);
	ft_printf("%.*d\n", -1, 0);
	printf("%.*d\n", -8, 0);
}*/