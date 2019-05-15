/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deci_exa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:20 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/15 19:10:16 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char    ft_bin_exa(int a, int b, int c, int d)
{
	int		res;

	a &= 1;
	b &= 1;
	c &= 1;
	d &= 1;
	res = ((a << 3) | (b << 2) | (c << 1) | (d << 0));
	return (res);
}

char	*ft_deci_exa(unsigned long int k, t_printf save, int *j)
{
	int		i;
	char	c;

	i = 63;
	ft_check(save, j);
	save.buf[*j] = '0';
	*j += 1;
	ft_check(save, j);
	save.buf[*j] = 'x';
	while (k >> i == 0 && k >> (i - 1) == 0 && k >> (i - 2) == 0
			&& k >> (i - 3) == 0)
		i -= 4;
	while (i % 4 != 0)
		i++;
	i--;
	while (i >= 0)
	{
		c = ft_bin_exa(k >> i, k >> (i - 1), k >> (i - 2), k >> (i - 3));
		if (c >= 10)
			ft_check(save, j);
			save.buf[*j] = (c - 10) + 'a';
		else
			ft_check(save, j);
			save.buf[*j] = c + '0';
		*j += 1;
		i -= 4;
	}
	return (save);
}
