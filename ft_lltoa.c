/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:55:26 by dberger           #+#    #+#             */
/*   Updated: 2019/05/26 18:32:55 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_neg(t_printf save, int *j, long long *type, long long *s)
{
	if (!save.precision && save.width && !(save.flags & F_MINUS)
			&& !(save.flags & F_ZERO))
		save = ft_check_add(save, j, '-');
	if (!save.precision && save.width && (save.flags & F_MINUS))
		save = ft_check_add(save, j, '-');
	if (!save.precision && (save.flags & F_MINUS) && !save.width)
		save = ft_check_add(save, j, '-');
	if (!save.precision && !save.width && !(save.flags & F_ZERO))
		save = ft_check_add(save, j, '-');
	if (!save.precision && !(save.width) && (save.flags & F_ZERO)
			&& !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '-');
	*type = -*type;
	*s -= 1;
	return (save);
}

t_printf	ft_plus(t_printf save, int *j)
{
	if (!save.width)
		save = ft_check_add(save, j, '+');
	if (save.width && !(save.flags & F_ZERO) && !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	if (save.width && (save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	return (save);
}

t_printf	ft_num(t_printf save, long long s, long long type, int *j)
{
	int			t;
	long long	ten;
	char		c;

	t = 1;
	ten = 0;
	if (type >= 10)
	{
		ten = 10;
		while (t < s)
		{
			ten = ten * 10;
			t++;
		}
	}
	while (ten >= 10)
	{
		c = (type / ten) + '0';
		type = type - ((type / ten) * ten);
		save = ft_check_add(save, j, c);
		ten = ten / 10;
	}
	c = type + '0';
	save = ft_check_add(save, j, c);
	return (save);
}

t_printf	ft_lltoa(t_printf save, int *j, long long type)
{
	long long	s;
	long long	ten;

	ten = 0;
	s = ft_sizenb_ll(type);
	if ((save.modif & M_H))
		s = ft_sizenb_ll(type);
	if (type >= 0 && !save.precision && (save.flags & F_PLUS))
		save = ft_plus(save, j);
	if (type == 0)
	{
		if (save.precision || save.flags & F_POINT)
			return (save);
		return (ft_check_add(save, j, '0'));
	}
	if (type < 0)
		save = ft_neg(save, j, &type, &s);
	s--;
	return (ft_num(save, s, type, j));
}
