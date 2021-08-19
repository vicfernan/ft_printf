/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_category_p_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:00:59 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:40:23 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

char	*ft_value_p(char *aux, int x, t_vari *select)
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

void	ft_size_len_p(t_vari *select, int size, char *inter)
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

void	ft_category_p(t_vari *select, char *aux, int length, int i)
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
