/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/14 19:00:48 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_format_di(t_printf save, va_list ap, int *j, char c)
{
	int		type;
	int		s;
	int		count;

	type = va_arg(ap, int);
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
