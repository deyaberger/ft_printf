/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/15 19:25:44 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_width_di(t_printf save, int *j, long long type)
{
	int			count;
	long long	s;
	int			w;

	w = save.width;
	s = ft_sizenb_ll(type);
	if (save.precision && s < save.precision)
		count = save.precision;
	else
		count = s;
	if (type > 0 && (save.flags & F_PLUS))
		count++;
	if (type > 0 && (save.flags & F_SPACE))
		count++;
	if (count < w)
	{
		if ((save.flags & F_ZERO) && !(save.precision) && !(save.flags & F_MINUS))
		{
			while (w - count)
			{
				if (*j == BUFF_SIZE && (*j = 0) == 0)
					write (1, &save.buf, BUFF_SIZE);
				save.buf[*j] = '0';
				w--;
				*j += 1;
			}
			return (save);
		}
		while (w - count)
		{
			if (*j == BUFF_SIZE && (*j = 0) == 0)
				write (1, &save.buf, BUFF_SIZE);
			save.buf[*j] = ' ';
			w--;
			*j += 1;
		}
	}
	return (save);
}

t_printf 	ft_precision_di(t_printf save, int *j, long long type)
{
	long long s;
	int p;

	s = ft_sizenb_ll(type);
	p = save.precision;
	if (s < p)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		if (type < 0)
		{
			save.buf[*j] = '-';
			*j += 1;
			type = -type;
		}
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		if (type > 0 &&  (save.flags & F_PLUS))
		{	
			save.buf[*j] = '+';
			*j += 1;
		}
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		while (p - s > 0)
		{
			if (*j == BUFF_SIZE && (*j = 0) == 0)
				write (1, &save.buf, BUFF_SIZE);
			save.buf[*j] = '0';
			*j += 1;
			p--;
		}
		save.buf[*j] = '\0';
	}
	return (save);
}

long long	ft_modif_di(t_printf save, va_list ap)
{
	long long	number;

	if (save.modif && (save.modif & M_HH))
		return (number = (char)va_arg(ap, int));
	if (save.modif && (save.modif & M_H))
		return (number = (short)va_arg(ap, int));
	if (save.modif && (save.modif & M_L))
		return (number = va_arg(ap, long));
	if (save.modif && (save.modif & M_LL))
		return (number = va_arg(ap, long long));
	return (number = va_arg(ap, int));
}

t_printf	ft_format_di(t_printf save, va_list ap, int *j)
{
	long long	type;

	type = ft_modif_di(save, ap);
	if (type > 0 && (save.flags & F_SPACE))
	{
		save.buf[*j] = ' ';
		*j += 1;
	}
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	if (save.precision)
		save = ft_precision_di(save, j, type);
	save = ft_lltoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	return (save);
}
