/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:18:36 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/10 18:08:14 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_zero2(char *add, unsigned long long p)
{
	unsigned long long	k;
	int					i;

	i = 0;
	k = 1;
	while (k != p)
	{
		k *= 5;
		i++;
	}
	k = 0;
	while (add[k])
		k++;
	while (add[k - 1] >= '0' && add[k - 1] <= '9')
	{
		i--;
		k--;
	}
	while (i != 0)
	{
		k = 0;
		while (add[k])
			k++;
		while (k > 0)
		{
			add[k] = add[k - 1];
			k--;
		}
		add[k] = '0';
		i--;
	}
	return (add);
}

char	*ft_add(char *add, char *tab)
{
	int		j;
	int		rest;

	j = 0;
	rest = 0;
	while (add[j])
		j++;
	while (j >= 0)
	{
		tab[j] = ((tab[j] == '\0') ? '0' : tab[j]);
		add[j] = ((add[j] == '\0') ? '0' : add[j]);
		add[j] += rest;
		if (((add[j] - '0') + (tab[j] - '0')) > 0)
		{
			rest = (((add[j] - '0') + (tab[j] - '0')) / 10);
			tab[j] = ((((add[j] - '0') + (tab[j] - '0')) % 10) + '0');
		}
		else
		{
			tab[j] = (((add[j] - '0') + (tab[j] - '0')) + '0');
			rest = 0;
		}
		j--;
	}
	j = 0;
	while (add[j])
		j++;
	tab[j - 1] = '\0';
	return (tab);
}

char	*ft_float2(unsigned long long vir, char *tab, int size, char *add)
{
	unsigned long long	k;
	unsigned long long	l;
	int					j;

	k = 5;
	while (size >= 0)
	{
		if (((vir >> size) & 1) == 1)
		{
			l = k;
			j = 0;
			while (l > 0)
			{
				add[j] = (l % 10) + '0';
				j++;
				l /= 10;
			}
			tab = ft_add(ft_zero2(ft_strrev(add), k), tab);
			ft_bzero(add, 2047);
		}
		size--;
		k *= 5;
	}
	return (tab);
}
