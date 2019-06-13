/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:37:41 by dberger           #+#    #+#             */
/*   Updated: 2019/06/13 14:50:18 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

t_printf	ft_w_add_f(t_printf save, int *j, int count, char *fix)
{
	long	s;
	int		w;

	w = save.width;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre == 6))
		s = ft_strlen(fix) + 7;
	else
		s = ft_strlen(fix) + save.pre + 1;
	if (fix[0] == '-' && save.pre > 0 && save.pre < s && w > s)
		count++;
	if (fix[0] == '-' && (save.flags & F_ZERO) && !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '-');
	if ((save.flags & F_ZERO) && !(save.flags & F_MINUS))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_width_f(t_printf save, int *j, char *fix, char *nb)
{
	int		count;
	long	s;

	s = ft_strlen(fix) + save.pre + 1;
	if (!(save.pre) && !(save.flags & F_POINT))
		s = ft_strlen(fix) + 7;
	count = save.width - s;
	if (save.pre && save.width > save.pre && s < save.pre)
		count = save.width - save.pre;
	if (save.pre && s < save.pre && save.width <= save.pre)
		return (save);
	if (save.flags & F_PLUS && fix[0] != '-')
	{
		if ((save.flags & F_ZERO) && !(save.flags & F_MINUS) && !(save.pre))
			save = ft_check_add(save, j, '+');
		count--;
	}
	if ((fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
			|| (fix[0] == '-' && save.pre))
		count--;
	if (fix[0] == '0' && nb[0] == '0' && !(save.pre) && (save.flags & F_POINT))
		count++;
	save = ft_w_add_f(save, j, count, fix);
	return (save);
}

t_printf	ft_nan_inf(t_printf save, int *j, char *str)
{
	int		i;

	i = 0;
	if (str[0] == 'i' && (save.flags & F_SPACE) && save.width <= (int)ft_strlen(str) && !(save.flags & F_MINUS) && !(save.min))
		save = ft_check_add(save, j, ' ');
	if (str[0] == 'i' && (save.flags & F_PLUS) && !(save.min))
		str = "+inf";
	if (str[0] == 'i' && (save.min))
		str = "-inf";
	if (!(save.flags & F_POINT))
		save.pre = -1;
	if ((str[0] == 'i') && (save.flags & F_SPACE) && (save.flags & F_MINUS) && (save.width))
	{
		save = ft_check_add(save, j, ' ');
		save.width -= 1;
	}
	if (save.flags & F_MINUS)
		while (str[i])
			save = ft_check_add(save, j, str[i++]);
	i = ((!str) ? 6 : ft_strlen(str));
	save.width -= i;
	i = 0;
	while (i++ < save.width)
		save = ft_check_add(save, j, ' ');
	i = 0;
	if (!(save.flags & F_MINUS))
		while (str[i])
			save = ft_check_add(save, j, str[i++]);
	return (save);
}

t_printf	ft_format_f(t_printf save, va_list ap, int *j)
{
	long double	f;
	char		fix[2048];
	char		nb[2048];
	unsigned long *var;
	int			i;

	i = 64;
	f = va_arg(ap, double);
	var = (unsigned long*)&f;
/*	printf("var[1]={");
	while (i >= 0)
	{
		printf("%lu", (var[1] >> i) & 1);
		i--;
	}
	printf("}\n");
	i = 64;
	printf("var[0]={");
	while (i >= 0)
	{
		printf("%lu", (var[0] >> i) & 1);
		i--;
	}
	printf("}\n");
	i = 64;
	printf("masque={");
	while (i >= 0)
	{
		printf("%ld", (0x7FFFFFFFFFFFFFFF >> i) & 1);
		//		printf("%ld", (0xC000000000000000 >> i) & 1);
		i--;
	}
	printf("}\n");
	printf("((var[1] >> 63) & 1) = %lu\n", ((var[1] >> 63) & 1));
*/	ft_bzero(fix, 2048);
	ft_bzero(nb, 2048);
	if ((var[0] & 0xC000000000000000) == 0xC000000000000000)
	{
		fix[0] = 'n';
		fix[1] = 'a';
		fix[2] = 'n';
		fix[3] = '\0';
		return (save = ft_nan_inf(save, j, fix));
	}
	if (((var[0] & 0x7FFFFFFFFFFFFFFF) == 0) && ((var[1] & 1) == 1))
	{
			if (f < 0)
				save.min = 1;
			fix[0] = 'i';
			fix[1] = 'n';
			fix[2] = 'f';
			fix[3] = '\0';
		return (save = ft_nan_inf(save, j, fix));
	}
	ft_float(f, fix, 1);
	ft_float(f, nb, 2);
	if (fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		save = ft_check_add(save, j, ' ');
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_f(save, j, fix, nb);
	if (fix[0] != '-' && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	save = ft_ftoa(save, j, fix, nb);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_f(save, j, fix, nb);
	return (save);
}
