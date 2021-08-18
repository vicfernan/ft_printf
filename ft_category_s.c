/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_category_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:18:48 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:45 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

void	ft_point2_s(char *aux, int i, t_vari *select, int length, int size)
{
	char	*temp;

	temp = ft_substr(aux, i - length, length - (i - select->point));
	if (ft_strchr(temp, '*') > 0)
		select->pad = va_arg(select->args, int);
	else
		select->pad = ft_atoi(temp);
	free(temp);
	size = its_negative(size, select);
	temp = ft_substr(aux, select->point + 1, (i - select->point) - 1);
	if (ft_strchr(temp, '*') > 0)
		select->space = va_arg(select->args, int);
	else
		select->space = ft_atoi(temp);
	free(temp);
}

int	ft_size_s(char *aux, int i, int length, t_vari *select)
{
	int		size;
	char	*temp;

	size = 0;
	if (select->point > 0)
		ft_point2_s(aux, i, select, length, size);
	else if (select->asterisk == 0)
	{
		temp = ft_substr(aux, i - length, length);
		size = ft_atoi(temp);
		free(temp);
		size = its_negative(size, select);
	}
	else
	{
		size = va_arg(select->args, int);
		size = its_negative(size, select);
	}
	select->pad = its_negative(select->pad, select);
	return (size);
}

void	ft_category_s(t_vari *select, char *aux, int length, int i)
{
	char	*str;
	int		size;
	int		len;

	size = ft_size_s(aux, i, length, select);
	str = va_arg(select->args, char *);
	if (str == NULL)
	{
		if (size == 0 && select->pad == 0)
		{
			size = select->space;
			if (size < 0 || size > 6)
				size = 6;
		}
		str = "(null)";
		select->is_null++;
	}
	len = (int)ft_strlen(str);
	if ((len > select->space && select->space >= 0) && select->point > 0)
		len = select->space;
	write_s(select, str, len, size);
}
