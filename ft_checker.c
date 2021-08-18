/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:50:48 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:47 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

int	its_negative(int num, t_vari *select)
{
	if (num < 0)
	{
		num *= -1;
		select->negative++;
	}
	return (num);
}

void	ft_check_sign(t_vari *select)
{
	if (select->sign > 0)
		select->width += write(1, "-", 1);
	else
		select->width += write(1, "+", 1);
}

int	ft_zero_len(t_vari *select, int size, char *inter)
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

int	ft_len_zero(t_vari *select, int size, char *inter, char fill)
{
	if (size > (int)ft_strlen(inter) && select->z > 0
		&& select->point > 0 && select->prueba > 0)
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

int	ft_neg_point_check(t_vari *select, int size, char *inter)
{
	char	fill;

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
