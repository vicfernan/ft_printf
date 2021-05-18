/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:35:11 by vifernan          #+#    #+#             */
/*   Updated: 2021/05/18 12:54:09 by vifernan         ###   ########.fr       */
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
	char		*temp;


	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != '%')
		{
			if (!final)
				final = ft_strdup(ft_char_to_string(input[i]));
			else
			{
				temp = ft_strjoin(final, ft_char_to_string(input[i]));
				free(final);
				final = temp;
			}
		}
		else
		{
			if (input[i] == '%' && input[i + 1] == 's')
			{
				if (!final)
					final = ft_strdup(va_arg(args, char*));
				else
				{
					temp = ft_strjoin(final, va_arg(args, char*));
					free(final);
					final = temp;
				}
				i++;
			}
			if (input[i] == '%' && input[i + 1] == 'c')
			{
				if (!final)
					final = ft_strdup(ft_char_to_string(va_arg(args, int)));
				else
				{
					temp = ft_strjoin(final, ft_char_to_string(va_arg(args, int)));
					free(final);
					final = temp;
				}
				i++;
			}
			if (input[i] == '%' && input[i + 1] == 'd')
			{
				if (!final)
					final = ft_strdup(ft_itoa(va_arg(args, int)));
				else
				{
					temp = ft_strjoin(final, ft_itoa(va_arg(args, int)));
					free(final);
					final = temp;
				}
				i++;
			}
		}
		i++;
	}
	ft_putstr_fd(final, 1);
	free(final);
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
	int a = 23;
	int b = -1;
	int c = 0;
	char d = 'V';
	char *e = "Hola";

	ft_printf("%d %d %d %s %cict%or          \n\n\n\n\n", a, b, c, e, d);
}
