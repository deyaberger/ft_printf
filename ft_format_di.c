/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/15 15:06:14 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_width_di(t_printf save, int *j, int type)
{
	int		count;
	int		s;
	int		w;

	w = save.width;
	s = ft_sizenb(type);
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
				save.buf[*j] = '0';
				w--;
				*j += 1;
			}
			return (save);
		}
		while (w - count)
		{
			save.buf[*j] = ' ';
			w--;
			*j += 1;
		}
	}
	return (save);
}

t_printf	ft_ditoa(t_printf save, int *j, int type)
{
	int		s;
	int		count;

	s = ft_sizenb(type);
	count = s;
	save.buf[*j + s] = '\0';
	if (type == 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		save.buf[*j] = '0';
		*j += 1;
		return (save);
	}
	if (type < 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		if (!save.precision)
		{
			save.buf[*j] = '-';
			*j += 1;
		}
		type = -type;
		s--;
		count--;
	}
	if (type > 0 && !save.precision && (save.flags & F_PLUS))
	{	
		save.buf[*j] = '+';
		*j += 1;
	}
	s--;
	while (s >= 0)
	{
		if (*j + s == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		save.buf[*j + s] = (type % 10 + '0');
		s--;
		type = type / 10;
	}
	*j = *j + count;
	return (save);
}

t_printf 	ft_precision_di(t_printf save, int *j, int type)
{
	int		s;
	int		p;

	s = ft_sizenb(type);
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
		if (type > 0 &&  (save.flags & F_PLUS))
		{	
			save.buf[*j] = '+';
			*j += 1;
		}
		while (p - s > 0)
		{
			save.buf[*j] = '0';
			*j += 1;
			p--;
		}
		save.buf[*j] = '\0';
	}
	return (save);
}

t_printf	ft_format_di(t_printf save, va_list ap, int *j)
{
	int		type;

	type = va_arg(ap, int);
	if (type > 0 && (save.flags & F_SPACE))
	{
		save.buf[*j] = ' ';
		*j += 1;
	}
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	if (save.precision)
		save = ft_precision_di(save, j, type);
	save = ft_ditoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	return (save);
}
