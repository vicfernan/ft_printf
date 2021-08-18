/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_on_off.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:52:47 by vifernan          #+#    #+#             */
/*   Updated: 2021/08/18 19:54:51 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"
#include <stdio.h>
#include <limits.h>

t_vari	*init_select(t_vari *select)
{
	select->width = 0;
	select->zero = 0;
	select->space = 0;
	select->point = 0;
	select->sign = 0;
	select->plus = 0;
	select->pad = 0;
	select->z = 0;
	select->s = 0;
	select->number = 0;
	select->negative = 0;
	select->asterisk = 0;
	select->is_null = 0;
	select->prueba = 0;
	return (select);
}

t_vari	*reset_select(t_vari *select)
{
	select->zero = 0;
	select->space = 0;
	select->point = 0;
	select->sign = 0;
	select->number = 0;
	select->plus = 0;
	select->s = 0;
	select->pad = 0;
	select->z = 0;
	select->negative = 0;
	select->asterisk = 0;
	select->is_null = 0;
	select->prueba = 0;
	return (select);
}
