/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:54 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/14 19:01:38 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_process(t_printf save, const char *restrict format, va_list ap)
{
	int		i;
	int		j;

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
			i = i + save.index;
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
	printf("\nflags : [%d]\nwidth : [%d]\nprecision : [%d]\nmodif : [%d]\nbuf : [%s]\n", save.flags, save.width, save.precision, save.modif, save.buf);
	return (0);
}

int		main(void)
{
	ft_printf("bonjour les %#0.10d personnes", 257);
	return (0);
}
