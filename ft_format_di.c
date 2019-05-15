/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/15 16:34:09 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

short	ft_modif_di(int type)
{
	short	sh;

	if (type == 32768)
		return (-32768);
	if (type > 32768 || type < -32768)
		return (32767);
	sh = type;
	return (sh);
}

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

t_printf	ft_ditoa(t_printf save, int *j, int type)
{
	int		s;
	int		count;
	long	t;

	t = type;
	s = ft_sizenb(t);
	count = s;
	save.buf[*j + s] = '\0';
	if ((save.modif & M_H))
	{
		t = ft_modif_di(type);
		s = ft_sizenb(t);
	}
	if (t == 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		save.buf[*j] = '0';
		*j += 1;
		return (save);
	}
	if (t < 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		if (!save.precision)
		{
			save.buf[*j] = '-';
			*j += 1;
		}
		t = -t;
		s--;
	}
	if (*j == BUFF_SIZE && (*j = 0) == 0)
		write (1, &save.buf, BUFF_SIZE);
	if (t > 0 && !save.precision && (save.flags & F_PLUS))
	{	
		save.buf[*j] = '+';
		*j += 1;
	}
	s--;
	while (s >= 0)
	{
		if (*j + s == BUFF_SIZE && (*j = 0) == 0)
			write (1, &save.buf, BUFF_SIZE);
		save.buf[*j + s] = (t % 10 + '0');
		s--;
		t = t / 10;
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
