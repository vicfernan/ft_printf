/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:39:31 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:42:05 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

int	ft_point_p_sp(char *aux, int length, t_vari *select, int size)
{
	char	*temp;

	temp = ft_substr(aux, select->value_i - (length - 1),
			(length - 1) - (select->value_i - select->point));
	if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
		select->space = va_arg(select->args, int);
	else
		select->space = ft_atoi(temp);
	if (select->space < 0)
		select->space *= -1;
	free(temp);
	return (select->space);
}

int	ft_point_sp(char *aux, int length, t_vari *select, int size)
{
	char	*temp;

	temp = ft_substr(aux, select->value_i - length,
			length - (select->value_i - select->point));
	if ((ft_strchr(temp, '*') > 0 || temp[size] == '*') && select->asterisk--)
		select->space = va_arg(select->args, int);
	else
	{
		if (temp[0] == '0')
			temp[0] = ' ';
		select->space = ft_atoi(temp);
	}
	if (select->space < 0)
	{
		select->space *= -1;
		select->negative++;
	}
	free(temp);
	return (select->space);
}

int	ft_point_z(char *aux, int i, t_vari *select, int size)
{
	char	*temp;

	temp = ft_substr(aux, select->point + 1, (i - select->point) - 1);
	if (temp[size] == '*' && select->asterisk--)
		select->zero = va_arg(select->args, int);
	else
		select->zero = ft_atoi(temp);
	if (select->zero < 0)
	{
		select->zero *= -1;
		if (select->zero > select->space)
		{
			select->negative++;
		}
		else
			select->prueba++;
		select->pad++;
	}
	free(temp);
	return (select->zero);
}

int	ft_ast(char *aux, int length, t_vari *select, int size)
{
	char	*temp;

	temp = ft_substr(aux, select->value_i - length, length);
	if (temp[0] == '0' || temp[1] == '0')
		select->z++;
	free(temp);
	size = va_arg(select->args, int);
	if (size < 0)
	{
		size *= -1;
		select->negative++;
	}
	return (size);
}

int	ft_nast_npoint(char *aux, int length, t_vari *select, int size)
{
	char	*temp;

	if (select->plus > 0)
	{
		temp = ft_substr(aux, select->plus + 1,
				(select->value_i - select->plus + 1));
		if (temp[1] == '0')
			select->z++;
		size = ft_atoi(temp);
		free(temp);
		if (size < 0 && select->negative++)
			size *= -1;
	}
	else
	{
		temp = ft_substr(aux, select->value_i - length, length);
		if (temp[1] == '0')
			select->z++;
		size = ft_atoi(temp);
		free(temp);
		if (size < 0)
			size *= -1;
	}
	return (size);
}
