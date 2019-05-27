/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_ou.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:54:04 by dberger           #+#    #+#             */
/*   Updated: 2019/05/27 17:44:09 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_width_ou(t_printf save, int *j, long long type)
{
	int			count;
	long long	s;
	int			w;

	w = save.width;
	s = ft_sizenb_ll(type);
	count = w - s;
	if (save.precision && w > save.precision && s < save.precision)
		count = w - save.precision;
	if (save.precision && s < save.precision && w <= save.precision)
		return (save);
	if (save.flags & F_PLUS && type >= 0)
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

t_printf	ft_precision_ou(t_printf save, int *j, long long type)
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
	if (type == 0 && save.precision > 0)
		save = ft_check_add(save, j, '0');
	return (save);
}

long long	ft_modif_ou(t_printf save, va_list ap)
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

t_printf	ft_format_ou(t_printf save, va_list ap, int *j, char c)
{
	long long	type;

	type = ft_modif_ou(save, ap);
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_ou(save, j, type);
	if (save.precision)
		save = ft_precision_ou(save, j, type);
	//	if (c == 'o')
	//		save = ft_otoa(save, j, type);
	//	else
	if (c == 'u')
	{
		if (save.flags & F_PLUS)
			save.flags -= F_PLUS;
		save = ft_lltoa(save, j, type);
	}
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_ou(save, j, type);
	return (save);
}
