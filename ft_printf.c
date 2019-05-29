/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/05/29 13:13:25 by dberger          ###   ########.fr       */
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
			save = ft_check_add(save, &j, format[i]);
			i++;
		}
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			save = ft_convert(save, (char*)&format[i + 1], ap, &j);
			i = i + save.index;
		}
		if (format[i] == '%' && format[i + 1] == '\0')
			i++;
	}
	save = ft_check_add(save, &j, '\0');
	j--;
	save.index = j;
	save.ret = save.ret + j;
	return (save);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_printf	save;

	save.ret = 0;
	save.buf[BUFF_SIZE] = '\0';
	va_start(ap, format);
	save = ft_process(save, format, ap);
	write(1, save.buf, save.index);
//	printf("\nflags : [%d]\nwidth : [%d]\nprecision : [%d]\nmodif : [%d]\n", save.flags, save.width, save.precision, save.modif);
	va_end(ap);
	return (save.ret);
}

/*int		main(void)
{
	ft_printf("%010s is a string", "this");
	printf("%010s is a string", "this");
	return (0);
}*/
