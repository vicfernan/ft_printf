/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillitup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:50:55 by vifernan          #+#    #+#             */
/*   Updated: 2021/06/29 17:24:51 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fillitup(char c, size_t n)
{
	char    *str;
    int     i;

    str = malloc(sizeof(char) * (n + 1));
    i = n - 1;
    while (i != 0)
        str[i--] = c;
    str[n + 1] = '\0';

    return (str);
}