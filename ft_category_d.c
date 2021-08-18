/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_category_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:36:57 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:39 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

int	ft_all_point_d(t_vari *select, char *aux, int i, int length)
{
	int	size;

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

char	*ft_value_u(t_vari *select)
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

char	*ft_value_d(t_vari *select)
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

int	ft_size_d(char *aux, int i, int length, t_vari *select)
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

void	ft_category_d(t_vari *select, char *aux, int length, int i)
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
