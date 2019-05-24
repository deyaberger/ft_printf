/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:34:43 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/24 18:35:52 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_print_ox(t_printf save, int *j, int mode)
{
	if ((save.flags & F_HASH) == F_HASH)
	{
		save = ft_check_add(save, j, '0');
		save = ft_check_add(save, j, (23 + mode));
	}
	return (save);
}

int			ft_len(t_printf save, unsigned long long nb, int mode)
{
	int		i;
	int		s;
	int		k;

	i = 63;
	if (nb != 0)
		while ((nb >> i | nb >> (i - 1) | nb >> (i - 2) | nb >> (i - 3)) == 0)
			i -= 4;
	while (i % 4 != 0)
		i++;
	if (mode == 0)
	{
		k = (save.precision - (i / 4));
		k < 0 ? k = 0 : 0;
		s = (save.width - ((i / 4) + 2)) - k;
		s < 0 ? s = 0 : 0;
	}
	else if (mode == 1)
	{
		s = (save.precision - (i / 4));
		s < 0 ? s = 0 : 0;
	}
	else
		((i - 1) < 0) ? (s = 0) : (s = i - 1);
	return (s);
}

t_printf	ft_print_h(t_printf save, int *j, unsigned long long nb, int mode)
{
	int		i;
	int		c;

	c = 0;
	i = ft_len(save, nb, 2);
	while (i > -1)
	{
		c = c | (((nb >> i) & 1) << 3);
		c = c | (((nb >> (i - 1)) & 1) << 2);
		c = c | (((nb >> (i - 2)) & 1) << 1);
		c = c | (((nb >> (i - 3)) & 1) << 0);
		//printf("\n\033[31m c : [%d]		mode : [%d]		i : [%d]\033[0m\n", c, mode, i);
		if (c >= 10)
		{
			save = ft_check_add(save, j, ((c - 10) + mode));
		printf("save.buf111=%c\n", save.buf[*j - 1]);
		printf("c11111=%d\n", c);
		}
		else
		{
			save = ft_check_add(save, j, (c + '0'));
		printf("save.buf=%c\n", save.buf[*j - 1]);
		printf("c2222=%d\n", c);
		}
		i -= 4;
		c = 0;
	}
	(void)mode;
	(void)*j;
	return (save);
}

t_printf	ft_form_xx(t_printf save, int *j, unsigned long long nb, int mode)
{
	int		s;
	int		s2;

	s = ft_len(save, nb, 0);
	s2 = ft_len(save, nb, 1);
	if ((save.flags & F_MINUS) == F_MINUS)
	{
		save = ft_print_ox(save, j, mode);
		if (save.precision != 0)
			while (s2-- != 0)
				save = ft_check_add(save, j, '0');
		ft_print_h(save, j, nb, mode);
	}
	if (save.width != 0 && (save.flags & F_ZERO) != F_ZERO)
		while (s-- != 0)
			save = ft_check_add(save, j, ' ');
	if ((save.flags & F_MINUS) != F_MINUS)
	{
		save = ft_print_ox(save, j, mode);
		if (save.width != 0 && (save.flags & F_ZERO) == F_ZERO)
			while (s-- != 0)
				save = ft_check_add(save, j, '0');
		if (save.precision != 0)
			while (s2-- != 0)
				save = ft_check_add(save, j, '0');
		ft_print_h(save, j, nb, mode);
	}
	return (save);
}

t_printf	ft_format_xx(t_printf save, va_list ap, int *j, char c)
{
	unsigned long long	number;

	if (save.modif && (save.modif & M_HH) == M_HH)
		number = (unsigned char)va_arg(ap, int);
	else if (save.modif && (save.modif & M_H) == M_H)
		number = (unsigned short)va_arg(ap, int);
	else if (save.modif && (save.modif & M_L) == M_L)
		number = va_arg(ap, unsigned long);
	else if (save.modif && (save.modif & M_LL) == M_LL)
		number = va_arg(ap, unsigned long long);
	number = va_arg(ap, unsigned int);
	if ((save.flags & F_MINUS) == F_MINUS && (save.flags & F_ZERO) == F_ZERO)
		save.flags -= F_ZERO;
	if (save.precision != 0 && (save.flags & F_ZERO) == F_ZERO)
		save.flags -= F_ZERO;
	if (c == 'x')
		save = ft_form_xx(save, j, number, (int)'a');
	else if (c == 'X')
		save = ft_form_xx(save, j, number, (int)'A');
	return (save);
}
