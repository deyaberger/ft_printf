/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:50:41 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/22 15:39:23 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		ft_bin_hexa(int a, int b, int c, int d)
{
	int		res;

	a &= 1;
	b &= 1;
	c &= 1;
	d &= 1;
	res = ((a << 3) | (b << 2) | (c << 1) | (d << 0));
	return (res);
}

t_printf	ft_init(t_printf save, int *j)
{
	ft_check(save, j);
	save.buf[*j] = '0';
	*j += 1;
	ft_check(save, j);
	save.buf[*j] = 'x';
	*j += 1;
	return (save);
}

t_printf	ft_dtoh(t_printf save, int *j, unsigned long int k, int i)
{
	char	c;

	save = ft_init(save, j);
	while (i >= 0)
	{
		c = ft_bin_hexa(k >> i, k >> (i - 1), k >> (i - 2), k >> (i - 3));
		ft_check(save, j);
		if (c >= 10)
			save.buf[*j] = (c - 10) + 'a';
		else
			save.buf[*j] = c + '0';
		*j += 1;
		i -= 4;
	}
	return (save);
}
