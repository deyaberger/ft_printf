/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/14 20:34:46 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_ditoa(t_printf save, int *j, int type)
{
	int		s;
	int		count;
	
	s = ft_sizenb(type);
	count = s;
	save.buf[*j + s] = '\0';
	if (type == 0)
	{
		save.buf[*j] = '0';
		*j += 1;
		return (save);
	}
	if (type < 0)
	{
		type = -type;
		save.buf[*j] = '-';
		*j += 1;
		s--;
		count--;
	}
	s--;
	while (s >= 0)
	{
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
	if (save.precision)
		save = ft_precision_di(save, j, type);
	save = ft_ditoa(save, j, type);
	return (save);
}
