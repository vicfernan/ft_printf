/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/05/12 17:25:06 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printflib.h"

char	*ft_char_to_string(char c)
{
	char *str;

	str = malloc(2 * sizeof(char));
	*str = c;
	str[1] = '\0';
	return (str);
}

int	ft_myprint(char *input, va_list args)
{
	int 		i;
	static char *final;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%' && input[i + 1] == 's')
			ft_putstr_fd(va_arg(args, char *), 1);
		if (input[i] == '%' && input[i + 1] == 'c')
			ft_putstr_fd(ft_char_to_string(va_arg(args, int)), 1);
		i++;
	}
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list		args;
	int			count;
	char		*aux;

	count = 0;
	aux = ft_strdup(input);
	va_start(args, input);
	ft_myprint(aux, args);
	va_end(args);
	return (count);
}

int main()
{
/*	int a = 23;
	int b = -1;
	int c = 0;*/
	char d = 'V';
	char *e = "Hola";

	ft_printf("%s %cictor\n", e, d);
}
