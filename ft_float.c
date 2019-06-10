/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:26:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/10 16:39:35 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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

char    *ft_add(char *add, char *tab)
{
	int     j;
	int     rest;

	j = 0;
	rest = 0;
//	printf("\033[32m add : [%s] \033[0m\n", add);
	while(add[j])
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
	while(add[j])
		j++;
	tab[j - 1] = '\0';
//	printf("\033[31m tab : [%s] \033[0m\n", tab);
	return (tab);
}

char	*ft_mode2(unsigned long long vir, char *tab, int size, char *add)
{
	unsigned long long  k;
	unsigned long long  l;
	int                 j;

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
	ft_bzero(add, 2047);
	p = (nb[1] & 0x7FFF) - 16382;
	ent = nb[0] >> (64 - p);
	vir = nb[0] << p;
	tab = m == 1 ? ft_mode1(ent, tab, p, add) : ft_mode2(vir, tab, 63, add);
	p = 0;
	while (tab[p])
		p++;
	((ent == 0 && m == 1) || (vir == 0 && m == 2)) ? tab[0] = '0' : 0;
}
/*
int		main(int argc, char **argv)
{
	long double			f;
	char				tab1[2048];
	char				tab2[2048];

	f = strtold(argv[1], NULL);
	ft_bzero(tab1, 2047);
	ft_bzero(tab2, 2047);
	ft_nico(f, tab1, 1);
	ft_nico(f, tab2, 2);
	printf("tab[F] : [%s.%s]\n", tab1, tab2);
	printf("tab[T] : [%.70Lf]\n", f);
	return (0);
}*/
