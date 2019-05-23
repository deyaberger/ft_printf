/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:56:50 by dberger           #+#    #+#             */
/*   Updated: 2019/05/23 15:58:23 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		ft_bin_oct(int a, int b, int c)
{
	int		res;

	a &= 1;
	b &= 1;
	c &= 1;
	res = ((a << 2) | (b << 1) | (c << 0));
	return (res);
}

t_printf	ft_otoa(t_printf save, int *j, long long type)
{
	char	c;
	int		i;

	i = 63;
	while ((type >> i | type >> (i - 1) | type >> (i - 2)) == 0)
		i -= 3;
	i--;
	while (i >= 0)
	{
		c = ft_bin_oct(type >> i, type >> (i - 1), type >> (i - 2));
		save = ft_check_add(save, j, (c + '0'));
		i -= 3;
	}
	return (save);
}
