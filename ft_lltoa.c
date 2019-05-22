/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:55:26 by dberger           #+#    #+#             */
/*   Updated: 2019/05/22 16:35:20 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_add_check(t_printf save, int *j, char c)
{
	ft_check_add(save, j, c);
	return (save);
}

t_printf	ft_neg(t_printf save, int *j, long long *type, long long *s)
{
	if (!save.precision)
		save = ft_add_check(save, j, '-');
	*type = -*type;
	*s -= 1;
	return (save);
}

t_printf	ft_lltoa(t_printf save, int *j, long long type)
{
	long long	s;
	long long	count;

	s = ft_sizenb_ll(type);
	count = s;
	if ((save.modif & M_H))
		s = ft_sizenb_ll(type);
	if (type >= 0 && !save.precision && !save.width && (save.flags & F_PLUS))
		save = ft_add_check(save, j, '+');
	if (type == 0)
		return (ft_add_check(save, j, '0'));
	if (type < 0)
		save = ft_neg(save, j, &type, &s);
	s--;
	while (s >= 0)
	{
		if (*j + s == BUFF_SIZE && (*j = 0) == 0)
			write(1, &save.buf, BUFF_SIZE);
		save.buf[*j + s] = (type % 10 + '0');
		s--;
		type = type / 10;
	}
	*j = *j + count;
	return (save);
}
