/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/06/03 17:01:26 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

int		main(int argc, char **argv)
{
	unsigned long int	tab[2];
	(void)argc;
	(void)argv;
	printf("f : [%lu]\n", sizeof(float));
	printf("f : [%lu]\n", sizeof(int));
	printf("lf : [%lu]\n", sizeof(double));
	printf("lf : [%lu]\n", sizeof(unsigned long int));
	printf("Lf : [%lu]\n", sizeof(long double));
	printf("Lf : [%lu]\n", sizeof(tab));
	
	printf("\ntest	 	: %%f 		: [%f]\n", strtof(argv[1], NULL));
	printf("test 		: %%0f 		: [%0f]\n", strtof(argv[1], NULL));
	printf("test 		: %% f 		: [% f]\n", strtof(argv[1], NULL));
	printf("test 		: %%20f 		: [%20f]\n", strtof(argv[1], NULL));
	printf("test 		: %%.20f 	: [%.20f]\n", strtof(argv[1], NULL));
	printf("test 		: %%#f 		: [%#f]\n", strtof(argv[1], NULL));
	printf("test 		: %%+f 		: [%+f]\n", strtof(argv[1], NULL));
	printf("test 		: %%-f 		: [%-f]\n", strtof(argv[1], NULL));
	printf("test 		: %%20.10f 	: [%20.10f]\n", strtof(argv[1], NULL));
	printf("test 		: %%10.20f 	: [%10.20f]\n", strtof(argv[1], NULL));
	printf("test 		: %%020f 	: [%020f]\n", strtof(argv[1], NULL));
	printf("test 		: %%0.20f 	: [%0.20f]\n\n", strtof(argv[1], NULL));
	printf("test 		: %%lf		: [%lf]\n", strtof(argv[1], NULL));
	printf("test 		: %%Lf		: [%Lf]\n", strtold(argv[1], NULL));
	printf("\n-------------------------------------------------------\n\n");
	ft_printf("ft_test 	: %%f 		: [%f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%0f 		: [%0f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %% f 		: [% f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%20f 		: [%20f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%.20f 	: [%.20f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%#f 		: [%#f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%+f 		: [%+f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%-f 		: [%-f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%20.10f 	: [%20.10f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%10.20f 	: [%10.20f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%020f 	: [%020f]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%0.20f 	: [%0.20f]\n\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%lf		: [%lf]\n", strtof(argv[1], NULL));
	ft_printf("ft_test 	: %%Lf		: [%Lf]\n\n", strtold(argv[1], NULL));
	
	ft_printf("ft_test 	: %%f 		: [%f]\n", strtof(argv[1], NULL));
	return (0);
}
