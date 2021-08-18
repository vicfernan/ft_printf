/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:00:26 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:55:00 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

int	ft_size_p(char *aux, int i, int length, t_vari *select)
{
	int		size;

	size = 0;
	if (aux[1] == '0')
		select->z++;
	if (select->point > 0)
	{
		if (select->plus > 0)
			select->space = ft_point_p_sp(aux, i, length, select, size);
		else
			select->space = ft_point_sp(aux, i, length, select, size);
		select->zero = ft_point_z(aux, i, select, size);
		if (select->space > select->zero)
			size = select->space;
		else
			size = select->zero;
	}
	if (select->asterisk > 0 && select->point == 0)
		size = ft_ast(aux, i, length, select, size);
	if (select->asterisk == 0 && select->point == 0)
		size = ft_nast_npoint(aux, i, length, select, size);
	return (size);
}

int	ft_numerlen(unsigned long long number)
{
	int	i;

	i = 0;
	while (number >= 16)
	{
		number /= 16;
		i++;
	}
	i++;
	return (i);
}

char	*ft_p_hexa(char *inter, char *aux, int x, t_vari *select)
{
	char	*hexa_g;
	int		i;
	int		j;

	i = (int)ft_strlen(inter);
	if (aux[x] == 'p')
	{
		hexa_g = malloc((i + 3) * sizeof(char));
		select->prueba++;
		hexa_g[0] = '0';
		hexa_g[1] = 'x';
		j = 2;
	}
	else
	{
		hexa_g = malloc(i + 1 * sizeof(char));
		j = 0;
	}
	while (--i >= 0)
		hexa_g[j++] = inter[i];
	hexa_g[j] = '\0';
	free(inter);
	return (hexa_g);
}
