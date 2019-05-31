/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/31 15:11:29 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_w_add(t_printf save, long type, int *j, int count)
{
	long	s;
	int		w;

	w = save.width;
	s = ft_sizenb_l(type);
	if (type < 0 && save.pre > 0 && save.pre < s && w > s)
		count++;
	if (type < 0 && (save.flags & F_ZERO) && !(save.flags & F_MINUS)
		&& !(save.pre))
		save = ft_check_add(save, j, '-');
	if ((save.flags & F_ZERO) && !(save.pre) && !(save.flags & F_MINUS))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	if (type == 0 && !(save.pre) && save.flags & F_POINT)
		save = ft_check_add(save, j, ' ');
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_width_di(t_printf save, int *j, long type)
{
	int		count;
	long	s;
	int		w;

	w = save.width;
	s = ft_sizenb_l(type);
	count = w - s;
	if (save.pre && w > save.pre && s < save.pre)
		count = w - save.pre;
	if (save.pre && s < save.pre && w <= save.pre)
		return (save);
	if (save.flags & F_PLUS && type >= 0)
	{
		if (save.flags & F_ZERO && !(save.flags & F_MINUS) && !(save.pre))
			save = ft_check_add(save, j, '+');
		count--;
	}
	if ((type >= 0 && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		|| (type < 0 && save.pre))
		count--;
	save = ft_w_add(save, type, j, count);
	return (save);
}

t_printf	ft_pre_di(t_printf save, int *j, long type)
{
	long	s;
	int		p;

	s = ft_sizenb_l(type);
	p = save.pre;
	if (type >= 0 && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	if (type < 0)
	{
		save = ft_check_add(save, j, '-');
		type = -type;
		s--;
	}
	if (s < p)
	{
		while (p - s > 0)
		{
			save = ft_check_add(save, j, '0');
			p--;
		}
	}
	if (type == 0 && save.pre > 0)
		save = ft_check_add(save, j, '0');
	return (save);
}

t_printf	ft_format_di(t_printf save, va_list ap, int *j)
{
	long	type;

	type = 0;
	if (save.modif && (save.modif & M_HH) && !(save.modif & M_L)
		&& !(save.modif & M_LL))
		type = (char)va_arg(ap, int);
	if (save.modif && (save.modif & M_H) && !(save.modif & M_L)
		&& !(save.modif & M_LL))
		type = (short)va_arg(ap, int);
	if (save.modif && (save.modif & M_L))
		type = va_arg(ap, long);
	if (save.modif && (save.modif & M_LL))
		type = va_arg(ap, long long);
	else if (!save.modif)
		type = va_arg(ap, int);
	if (type >= 0 && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		save = ft_check_add(save, j, ' ');
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	if (save.pre)
		save = ft_pre_di(save, j, type);
	save = ft_ltoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	return (save);
}
