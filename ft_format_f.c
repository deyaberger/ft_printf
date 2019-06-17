/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:37:41 by dberger           #+#    #+#             */
/*   Updated: 2019/06/14 15:04:09 by dberger          ###   ########.fr       */
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
	if (fix[0] == '0' && fix[1] == '\0' && nb[0] == '0' && nb[1] == '\0'
			&& !(save.pre) && (save.flags & F_POINT))
		count++;
	save = ft_w_add_f(save, j, count, fix);
	return (save);
}

void		ft_handlezero(char *fix, unsigned long *var, t_printf *save)
{
	save->min = 0;
	if (fix[0] == '\0' || (fix[0] == '-' && fix[1] == '\0'))
	{
		if (((var[1] >> 15) & 1) == 1)
		{
			fix[0] = '-';
			fix[1] = '0';
			fix[2] = '\0';
		}
		else
		{
			fix[0] = '0';
			fix[1] = '\0';
		}
	}
}

t_printf	ft_format_f(t_printf save, va_list ap, int *j)
{
	long double		f;
	char			fix[2048];
	char			nb[2048];
	unsigned long	*var;

	f = va_arg(ap, double);
	var = (unsigned long*)&f;
	ft_bzero(fix, 2048);
	ft_bzero(nb, 2048);
	save = ft_nan_inf(save, j, var, f);
	if (save.min != -42)
		return (save);
	ft_float(f, fix, 1);
	ft_float(f, nb, 2);
	ft_handlezero(fix, var, &save);
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
