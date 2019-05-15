/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:54 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/15 19:08:36 by dberger          ###   ########.fr       */
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
				write(1, save.buf, BUFF_SIZE);
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
	save.index = j;
	return (save);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_printf	save;

	save.buf[BUFF_SIZE] = '\0';
	va_start(ap, format);
	save = ft_process(save, format, ap);
	write(1, save.buf, save.index);
	va_end(ap);
//	printf("\nflags : [%d]\nwidth : [%d]\nprecision : [%d]\nmodif : [%d]\nbuf : [%s]\n", save.flags, save.width, save.precision, save.modif, save.buf);
	return (0);
}

int		main(void)
{
	int	i;

	i = 21;
	ft_printf("bonjour les %d personnes\n", i);
	//	printf("bonjour les %d personnes\n", &c);
	return (0);
}
