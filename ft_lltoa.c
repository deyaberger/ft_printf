/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:55:26 by dberger           #+#    #+#             */
/*   Updated: 2019/05/23 11:50:27 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_neg(t_printf save, int *j, long long *type, long long *s)
{
	if (!save.precision)
		save = ft_check_add(save, j, '-');
	*type = -*type;
	*s -= 1;
	return (save);
}

int			ft_ten(long long s)
{
	int	t;
	int	ten;

	t = 1;
	ten = 10;
	while (t < s)
	{
		ten = ten * 10;
		t++;
	}
	return (ten);
}

t_printf	ft_lltoa(t_printf save, int *j, long long type)
{
	long long	s;
	int			ten;
	char		c;

	s = ft_sizenb_ll(type);
	if ((save.modif & M_H))
		s = ft_sizenb_ll(type);
	if (type >= 0 && !save.precision && !save.width && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	if (type == 0)
		return (ft_check_add(save, j, '0'));
	if (type < 0)
		save = ft_neg(save, j, &type, &s);
	s--;
	ten = ft_ten(s);
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
