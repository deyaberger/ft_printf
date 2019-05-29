/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/05/29 16:27:59 by ncoursol         ###   ########.fr       */
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
	save.precision = 0;
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
