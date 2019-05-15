/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:55:26 by dberger           #+#    #+#             */
/*   Updated: 2019/05/15 19:18:34 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_null(t_printf save, int **j)
{
	if (**j == BUFF_SIZE && (**j = 0) == 0)
		write(1, &save.buf, BUFF_SIZE);
	save.buf[**j] = '0';
	**j += 1;
	return (save);
}

int			ft_neg(t_printf *save, int *j, long long type, long long *s)
{
	if (*j == BUFF_SIZE && (*j = 0) == 0)
		write(1, &save->buf, BUFF_SIZE);
	if (!save->precision)
	{
		save->buf[*j] = '-';
		*j += 1;
	}
	type = -type;
	s--;
	return (*j);
}

int			ft_plus(t_printf *save, int *j)
{
	save->buf[*j] = '+';
	*j += 1;
	return (*j);
}

t_printf	ft_lltoa(t_printf save, int *j, long long type)
{
	long long	s;
	long long	count;

	s = ft_sizenb_ll(type);
	count = s;
	save.buf[*j + s] = '\0';
	if ((save.modif & M_H))
		s = ft_sizenb_ll(type);
	if (type == 0)
		return (ft_null(save, &j));
	if (type < 0)
		*j = ft_neg(&save, j, type, &s);
	if (*j == BUFF_SIZE && (*j = 0) == 0)
		write(1, &save.buf, BUFF_SIZE);
	if (type > 0 && !save.precision && (save.flags & F_PLUS))
		*j = ft_plus(&save, j);
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
