/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:23:31 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:55:08 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

void	wr_point_neg_s(t_vari *select, char *str, int len, int x)
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

void	wr_point_pos_s(t_vari *select, char *str, int len, int x)
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

void	wr_size_len(t_vari *select, char *str, int len, int x, int size)
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

void	wr_len(t_vari *select, char *str, int len, int x)
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
