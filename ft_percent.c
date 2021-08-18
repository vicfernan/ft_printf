/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:54:53 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:54 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

void	ft_size_percent(t_vari *select, char c, char fill, int size)
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

void	ft_category_percent(t_vari *select, char *aux, int length, int i)
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
