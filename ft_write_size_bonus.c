/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_size_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:45:05 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:42:50 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

void	ft_s_neg_point(t_vari *select, int size, char *inter)
{
	int	i;

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

void	ft_s_neg(t_vari *select, int size, char *inter)
{
	int	i;

	i = 0;
	if (select->sign > 0 && size--)
		ft_check_sign(select);
	while (inter[i] != '\0' && size--)
		select->width += write(1, &inter[i++], 1);
	while (size-- > 0)
		select->width += write(1, " ", 1);
}

void	ft_point(t_vari *select, int size, char *inter)
{
	int	i;

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

void	ft_z_check(t_vari *select, int size, char *inter)
{
	int	i;

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

void	ft_size_len_d(t_vari *select, char *inter, int size)
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
