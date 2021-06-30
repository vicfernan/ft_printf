/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/06/30 17:14:07 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>

vari	*init_select(vari *select)
{
	select->width = 0;
	select->zero = 0;
	select->space = 0;
	select->point = 0;
	select->plus = 0;
	select->pad = 0;
	select->negative = 0;
	select->asterisk = 0;

	return (select);
}

int ft_percent(char *aux, int i, va_list args, vari *select)
{
	int 		length;
	char		*temp;
	int 		size;
	char		c;

	length = 0;
	select->negative = 0;
	select->asterisk = 0;
	size = 0;
	while (aux[i++] != 'c')
	{
		if (aux[i] == '-')
			select->negative++;
		if (aux[i] == '*')
			select->asterisk++;
		length++;
	}
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
	c = va_arg(args, int);
	if (size > 1)
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
	return (length);
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

/*int main()
{
	//int a = 23;
	//char b = 'i';
	//char c = 'c';
	//char d = 'V';
	//char e = '&';
	//long l = -8723647987432;

	//ft_printf("*** %-10c hola %c%c%c %*c\n", 'c', d, b, c, 100, e);
	//printf("*** %-10c hola %c%c%c %*c\n", 'c', d, b, c, 100, e);
	//printf("*PRINTF* %d %i %zu %d %s %cictor          \n\n\n\n\n", a, b, l, c, e, d);
	ft_printf("%*c\n", 2, '0');
	printf("%*c\n", 2, '0');
}*/
