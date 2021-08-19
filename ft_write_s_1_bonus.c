/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:21:31 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:42:35 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

void	wr_negative_null(t_vari *select, int size, char *str, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		select->width += write(1, &str[x++], 1);
		size--;
	}
	while (size-- > 0)
		select->width += write(1, " ", 1);
}

void	wr_null(t_vari *select, int size, char *str, int len)
{
	int	x;

	x = 0;
	if (select->is_null > 0 && select->point > 0
		&& size == 0 && select->zero == 0)
		size = 0;
	else if (select->space <= 0 && select->pad <= 0 && select->point > 0)
	{
		while (x < (int)ft_strlen(str))
			select->width += write(1, &str[x++], 1);
	}
	else if (select->negative > 0)
		wr_negative_null(select, size, str, len);
	else
	{
		while (size-- > len)
			select->width += write(1, " ", 1);
		while (len-- > 0)
			select->width += write(1, &str[x++], 1);
	}
}

void	write_s(t_vari *select, char *str, int len, int size)
{
	int	x;

	x = 0;
	if (select->is_null > 0)
	{
		if (select->pad > size)
			size = select->pad;
		wr_null(select, size, str, len);
	}
	else if (select->point > 0)
	{
		if (select->negative > 0)
			wr_point_neg_s(select, str, len, x);
		else
			wr_point_pos_s(select, str, len, x);
	}
	else if (size > len)
		wr_size_len(select, str, len, size);
	else
		wr_len(select, str, x);
}
