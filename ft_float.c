/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:26:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/10 18:09:56 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_zero(char *add, int size, int mode)
{
	unsigned long long	i;
	int					k;

	i = (mode == 1) ? 1 : 5;
	k = 0;
	while (k < size)
	{
		i *= (mode == 1) ? 2 : 5;
		k++;
	}
	k = 0;
	while (i > 9)
	{
		i /= 10;
		k++;
	}
	i = 0;
	while (k >= 0)
	{
		if (add[i] < '0' || add[i] > '9')
			add[i] = '0';
		k--;
		i++;
	}
	return (ft_strrev(add));
}

char	*ft_mode1(unsigned long long ent, char *tab, int size, char *add)
{
	unsigned long long	k;
	unsigned long long	l;
	int					j;
	int					i;

	k = 1;
	i = 0;
	while (i < size)
	{
		if (((ent >> i) & 1) == 1)
		{
			l = k;
			j = 0;
			while (l > 0)
			{
				add[j] = (l % 10) + '0';
				j++;
				l /= 10;
			}
			tab = ft_add(ft_zero(add, size, 1), tab);
			ft_bzero(add, 2047);
		}
		i++;
		k *= 2;
	}
	return (tab);
}

void	ft_float(long double f, char *tab, int m)
{
	unsigned long long	*nb;
	unsigned long long	ent;
	unsigned long long	vir;
	unsigned long long	p;
	char				add[2048];

	nb = (unsigned long long*)&f;
	ft_bzero(add, 2048);
	p = (nb[1] & 0x7FFF) - 16382;
	ent = nb[0] >> (64 - p);
	vir = nb[0] << p;
	tab = m == 1 ? ft_mode1(ent, tab, p, add) : ft_float2(vir, tab, 63, add);
	((ent == 0 && m == 1) || (vir == 0 && m == 2)) ? tab[0] = '0' : 0;
	p = 0;
	while (tab[p])
		p++;
	if ((nb[1] >> 15) & 1 && m == 1)
	{
		while (p != 0)
		{
			tab[p] = tab[p - 1];
			p--;
		}
		tab[0] = '-';
	}
}
