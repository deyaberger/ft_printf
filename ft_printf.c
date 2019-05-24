/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/05/24 19:03:40 by dberger          ###   ########.fr       */
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
			if ((j == BUFF_SIZE) && (j = 0) == 0)
			{
				save.ret = save.ret + BUFF_SIZE;
				write(1, &save.buf, BUFF_SIZE);
			}
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
	save = ft_check_add(save, &j, '\0');
	j--;
	save.index = j;
	save.ret = save.ret + j;
	return (save);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_printf	save;
	
	save.flags = 0;
	save.width = 0;
	save.precision = 0;
	save.modif = 0;
	save.index = 0;
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
	int	i;

	i = 21;
//	ft_printf("test");
//	ft_printf("%5+d", 42);
	ft_printf("%d%d%d%d%d", 1, -2, 3, -4, 5);
	printf("\n%d%d%d%d%d", 1, -2, 3, -4, 5);
//	printf("test");
	return (0);
}*/
