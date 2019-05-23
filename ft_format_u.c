/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:53:58 by dberger           #+#    #+#             */
/*   Updated: 2019/05/23 14:09:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_width_u(t_printf save, int *j, long long type)
{
	int			count;
	long long	s;
	int			w;

	w = save.width;
	s = ft_sizenb_ll(type);
	count = w - s;
	if (save.precision && w > save.precision && s < save.precision)
		count = w - save.precision;
	if (save.precision && s < save.precision && w < save.precision)
		return (save);
	if ((save.flags & F_ZERO) && !(save.precision) && !(save.flags & F_MINUS))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_precision_u(t_printf save, int *j, long long type)
{
	long long	s;
	int			p;

	s = ft_sizenb_ll(type);
	p = save.precision;
	if (s < p)
	{
		while (p - s > 0)
		{
			save = ft_check_add(save, j, '0');
			p--;
		}
	}
	return (save);
}

long long	ft_modif_u(t_printf save, va_list ap)
{
	long long	number;

	if (save.modif && (save.modif & M_HH))
		return (number = (unsigned char)va_arg(ap, unsigned int));
	if (save.modif && (save.modif & M_H))
		return (number = (unsigned short)va_arg(ap, unsigned int));
	if (save.modif && (save.modif & M_L))
		return (number = va_arg(ap, unsigned long));
	if (save.modif && (save.modif & M_LL))
		return (number = va_arg(ap, unsigned long long));
	return (number = va_arg(ap, unsigned int));
}

t_printf	ft_format_u(t_printf save, va_list ap, int *j)
{
	long long	type;

	type = ft_modif_u(save, ap);
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	if (save.precision)
		save = ft_precision_u(save, j, type);
	save = ft_lltoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	return (save);
}
