/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:13:39 by dberger           #+#    #+#             */
/*   Updated: 2019/05/27 19:00:38 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_print_pref(t_printf save, int *j, int nb)
{
	if (nb == 0)
		return (save);
	if ((save.flags & F_HASH) == F_HASH)
		save = ft_check_add(save, j, '0');
	return (save);
}

int			ft_len3(t_printf save, unsigned long long nb, int mode)
{
	int		i;
	int		s;
	int		k;

	i = 63;
	if (nb != 0)
		while ((nb >> i | nb >> (i - 1) | nb >> (i - 2)) == 0)
			i -= 3;
	while (i % 3 != 0)
		i++;
	if (nb == 0)
		i = ((save.precision == 0 && (save.flags & F_POINT)) ? -1 : 3);
	if (mode == 0)
	{
		k = ((save.precision - (i / 3)) < 0 ? 0 : save.precision - (i / 3));
		s = ((save.width - ((i / 3) - k)) < 0 ? 0 : save.width - ((i / 3) - k));
		(nb == 0) ? (s++) : 0;
		s = (save.flags & F_HASH)
			|| (save.precision == 0 && (save.flags & F_POINT)) ? s-- : s;
	}
	else if (mode == 1)
		s = ((save.precision - (i / 3)) < 0 ? 0 : save.precision - (i / 3));
	else
		s = (((i - 1) < 0) ? -1 : (i - 1));
	return (s);
}

t_printf	ft_print_o(t_printf save, int *j, unsigned long long nb)
{
	int		i;
	int		c;
	int		s2;

	c = 0;
	s2 = ft_len3(save, nb, 1);
	if (save.precision != 0)
		while (s2-- != 0)
			save = ft_check_add(save, j, '0');
	i = ft_len3(save, nb, 2);
	while (i > -1)
	{
		c = c | (((nb >> i) & 1) << 2);
		c = c | (((nb >> (i - 1)) & 1) << 1);
		c = c | (((nb >> (i - 2)) & 1) << 0);
		save = ft_check_add(save, j, (c + '0'));
		i -= 3;
		c = 0;
	}
	return (save);
}

t_printf	ft_form_o(t_printf save, int *j, unsigned long long nb)
{
	int		s;

	s = ft_len3(save, nb, 0);
	if ((save.flags & F_MINUS))
	{
		save = ft_print_pref(save, j, nb);
		save = ft_print_o(save, j, nb);
	}
	if (save.width != 0 && !(save.flags & F_ZERO))
	{
		if (save.flags & F_HASH && nb != 0)
				s--;
		while (s-- != 0)
			save = ft_check_add(save, j, ' ');
	}
	if (!(save.flags & F_MINUS))
	{
		save = ft_print_pref(save, j, nb);
		if (save.width != 0 && (save.flags & F_ZERO))
			while (s-- != 0)
				save = ft_check_add(save, j, '0');
		save = ft_print_o(save, j, nb);
	}
	return (save);
}

t_printf	ft_format_o(t_printf save, va_list ap, int *j)
{
	unsigned long long	number;

	if (save.modif && (save.modif & M_HH))
		number = (unsigned char)va_arg(ap, int);
	else if (save.modif && (save.modif & M_H))
		number = (unsigned short)va_arg(ap, int);
	else if (save.modif && (save.modif & M_L))
		number = va_arg(ap, unsigned long);
	else if (save.modif && (save.modif & M_LL))
		number = va_arg(ap, unsigned long long);
	else
		number = va_arg(ap, unsigned int);
	if ((save.flags & F_MINUS) && (save.flags & F_ZERO))
		save.flags -= F_ZERO;
	if (save.precision != 0 && (save.flags & F_ZERO))
		save.flags -= F_ZERO;
	save = ft_form_o(save, j, number);
	return (save);
}
