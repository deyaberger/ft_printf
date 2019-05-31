/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/05/31 14:33:24 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_format(char c, t_printf save, va_list ap, int *j)
{
	if (c == 'c' || c == 's' || c == 'p')
		save = ft_format_csp(save, ap, j, c);
	else if (c == 'd' || c == 'i')
		save = ft_format_di(save, ap, j);
	else if (c == 'x' || c == 'X')
		save = ft_format_xx(save, ap, j, c);
	else if (c == 'f')
		save = ft_format_f(save, ap, j);
	else if (c == 'o')
		save = ft_format_o(save, ap, j);
	else if (c == 'u')
		save = ft_format_u(save, ap, j);
	else if (c == 'b')
		save = ft_format_b(save, ap, j);
	else if (c == '%')
		save = ft_format_pct(save, j);
	return (save);
}

t_printf	ft_init(t_printf save, char *str, va_list ap, int *j)
{
	int		i;
	int		s;

	i = 0;
	save.flags = 0;
	save.width = 0;
	save.pre = 0;
	save.modif = 0;
	save.min = 0;
	save.index = 1;
	save = ft_convert(save, str, &i, &s);
	if (s == 2)
	{
		save.index = i + 2;
		save = ft_format(str[i], save, ap, j);
	}
	return (save);
}

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
			save = ft_init(save, (char*)&format[i + 1], ap, &j);
			i += save.index;
		}
		if (format[i] == '%' && format[i + 1] == '\0')
			i++;
	}
	save = ft_check_add(save, &j, '\0');
	j--;
	save.index = j;
	save.ret += j;
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
	va_end(ap);
	return (save.ret);
}

/*int		main(void)
{
	ft_printf("%llo\n", (unsigned long long)-125);
	printf("%llo\n", (unsigned long long)-125);
	printf("********\n");
	ft_printf("@moulitest: %#.o %#.0o\n", 0, 0);
	printf("@moulitest: %#.o %#.0o\n", 0, 0);
	printf("********\n");
	ft_printf("%#o\n", 0);
	printf("%#o\n", 0);
	printf("********\n");
	ft_printf("t[%04.2o][%#2o]et [%#-8.3o] titi\n", 0, 0, 0);
	printf("t[%04.2o][%#2o]et [%#-8.3o] titi\n", 0, 0, 0);
	printf("********\n");
	ft_printf("test[%#.4o] et [%#.5o] et [%#.o]\n", 13, 13, 13);
	printf("test[%#.4o] et [%#.5o] et [%#.o]\n", 13, 13, 13);
	printf("********\n");
	ft_printf("m%#.9od\n", 123456789);
	printf("m%#.9od\n", 123456789);
	printf("********\n");
	ft_printf("test%#.4o et %02o %0#14.0o!!\n", 012, 036, 12587499);
	printf("test%#.4o et %02o %0#14.0o!!\n", 012, 036, 12587499);
	printf("********\n");
	ft_printf("%05.o\n", 42);
	printf("%05.o\n", 42);
	return (0);
}*/
