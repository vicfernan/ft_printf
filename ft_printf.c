/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:56 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

void	ft_checker(char *aux, int i, t_vari *select)
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

int	ft_percent(char *aux, int i, t_vari *select)
{
	int	length;

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

int	myprintf(char *aux, va_list args, t_vari *select)
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
	t_vari	*select;
	int		count;
	char	*aux;

	select = (t_vari *)malloc(sizeof(t_vari));
	if (!select)
		return (-1);
	init_select(select);
	count = 0;
	aux = (char *)input;
	va_start(select->args, input);
	count = myprintf(aux, select->args, select);
	va_end(select->args);
	free(select);
	return (count);
}
