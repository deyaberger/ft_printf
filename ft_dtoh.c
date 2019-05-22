/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:50:41 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/22 16:52:09 by ncoursol         ###   ########.fr       */
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

t_printf	ft_dtoh(t_printf save, int *j, unsigned long int k, int i)
{
	char	c;

	printf("BONJOUR 4\n");
	save = ft_check_add(save, j, '0');
	save = ft_check_add(save, j, 'x');
	while (i >= 0)
	{
		c = ft_bin_hexa(k >> i, k >> (i - 1), k >> (i - 2), k >> (i - 3));
		if (c >= 10)
			save = ft_check_add(save, j, ((c - 10) + 'a'));
		else
			save = ft_check_add(save, j, (c + '0'));
		i -= 4;
	}
	return (save);
}
