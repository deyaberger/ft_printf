/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:54 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/13 19:39:28 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_process(t_printf save, const char *restrict format, va_list ap)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	while (format[i])
	{
		while (format[i] && format[i] != '%')
		{
			if (j == BUFF_SIZE && (j = 0) == 0)
				printf("%s", save.buf);
			save.buf[j] = format[i];
			i++;
			j++;
		}
		if (format[i] == '%')
		{
			save = ft_convert(save, (char*)&format[i + 1], ap, &j);
			i += 2;
			// il faudrait refaire un calcul du i
		}
	}
	save.buf[j] = '\0';
	return (save);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_printf	save;

	save.buf[BUFF_SIZE] = '\0';
	va_start(ap, format);
	save = ft_process(save, format, ap);
	printf("%s\n", save.buf);
	va_end(ap);
	return (0);
}
