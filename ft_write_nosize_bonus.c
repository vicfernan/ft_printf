/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nosize_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:49:07 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/19 17:42:25 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

void	ft_nosize_d(t_vari *select, char *inter, int size)
{
	int	i;

	i = 0;
	if (size == 0 && inter[i] == '0'
		&& select->point == 0 && select->prueba == 0)
		select->width += write(1, "0", 1);
	else if (select->number > 0 && size == 0
		&& (select->point > 0 || select->asterisk > 0))
		select->number++;
	else
	{
		if (select->plus > 0)
			ft_check_sign(select);
		while (inter[i] != '\0')
			select->width += write(1, &inter[i++], 1);
	}
}
