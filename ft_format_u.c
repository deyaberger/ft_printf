/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:11:54 by dberger           #+#    #+#             */
/*   Updated: 2019/05/29 16:08:45 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		ft_width_u(t_printf save, int *j, unsigned long type)
{
	int				count;
	unsigned long	s;
	int				w;

	w = save.width;
	s = ft_sizenb_u(type);
	count = w - s;
	if (save.precision && w > save.precision && s < save.precision)
		count = w - save.precision;
	if (save.precision && s < save.precision && w <= save.precision)
		return (save);
	if (save.flags & F_PLUS)
		count--;
	if ((save.flags & F_ZERO) && !(save.precision) && !(save.flags & F_MINUS))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	if (type == 0 && !(save.precision) && save.flags & F_POINT)
		save = ft_check_add(save, j, ' ');
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf		ft_precision_u(t_printf save, int *j, unsigned long type)
{
	unsigned long	s;
	int				p;

	s = ft_sizenb_u(type);
	p = save.precision;
	if (s < p)
	{
		while (p - s > 0)
		{
			save = ft_check_add(save, j, '0');
			p--;
		}
	}
	if (type == 0 && save.precision > 0)
		save = ft_check_add(save, j, '0');
	return (save);
}

unsigned long	ft_modif_u(t_printf save, va_list ap)
{
	unsigned long	number;

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

t_printf		ft_format_u(t_printf save, va_list ap, int *j)
{
	unsigned long	type;

	type = ft_modif_u(save, ap);
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	if (save.precision)
		save = ft_precision_u(save, j, type);
	if (save.flags & F_PLUS)
		save.flags -= F_PLUS;
	save = ft_utoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	return (save);
}
