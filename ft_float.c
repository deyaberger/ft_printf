/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:26:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/14 14:37:28 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *ft_zero(char *add, int size)
{
	int		i;

	i = 0;
	while (size >= 0)
	{
		if (add[i] < '0' || add[i] > '9')
			add[i] = '0';
		i++;
		size--;
	}
	return (ft_strrev(add));
}

char    *ft_add2(char *add, char *tab)
{
	int     j;
	int     rest;

	j = 0;
	rest = 0;
	if (tab[0] == '1' && tab[1] == '\0')
		tab[0] = '\0';
	while (add[j])
		j++;
	while (j >= 0)
	{
		tab[j] = ((tab[j] == '\0') ? '0' : tab[j]);
		add[j] = ((add[j] == '\0' && j == 0) ? '0' : add[j]);
		add[j] += rest;
		if (((add[j] - '0') + (tab[j] - '0')) > 9)
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
		if (rest != 0 && j < 0)
		{
			j = 0;
			while (tab[j])
				j++;
			while (j > 0)
			{
				tab[j] = tab[j - 1];
				j--;
			}
			tab[j] = (rest + '0');
			j--;
		}
	}
	return (tab);
}

char    *ft_add(char *add, char *tab)
{
	int     j;
	int		k;
	int     rest;

	j = 0;
	k = 0;
	rest = 0;
	while (add[k + 1])
		k++;
	while (j <= k)
	{
		tab[j] = ((tab[j] == '\0') ? '0' : tab[j]);
		add[j] = ((add[j] == '\0' && j == 0) ? '0' : add[j]);
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
		j++;
		if (rest != 0 && j > k)
		{
			j = 0;
			while (tab[j])
				j++;
			tab[j] = (rest + '0');
			j = k + 1;
		}
	}
	return (ft_strrev(tab));
}

char    *ft_mult(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;

	ft_bzero(add, 5000);
	while (i > 0)
	{
		j = 0;
		rest = 0;
		add[j] = (add[j] == '\0') ? '1' : add[j];
		while (add[j + 1])
			j++;
		while (j >= 0)
		{
			if (((add[j] - '0') * 2) + rest > 9)
			{
				k = rest;
				rest = ((((add[j] - '0') * 2) + rest) / 10);
				add[j] = ((((add[j] - '0') * 2) + k) % 10) + '0';
			}
			else
			{
				add[j] = (((add[j] - '0') * 2) + rest) + '0';
				rest = 0;
			}
			j--;
			if (rest != 0 && j < 0)
			{
					j = 0;
					while (add[j])
						j++;
					while (j > 0)
					{
						add[j] = add[j - 1];
						j--;
					}
					add[0] = (rest + '0');
				j = -1;
			}
		}
		i--;
	}
	add[0] = (add[0] == '\0') ? '1' : add[0];
	return (ft_add(ft_strrev(add), ft_strrev(tab)));
}

char    *ft_mult2(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;
	int		l;

	l = i;
	ft_bzero(add, 5000);
	while (i >= 0)
	{
		j = 0;
		rest = 0;
		add[j] = (add[j] == '\0') ? '1' : add[j];
		while (add[j + 1])
			j++;
		while (j >= 0)
		{
			if (((add[j] - '0') * 5) + rest > 9)
			{
				k = rest;
				rest = ((((add[j] - '0') * 5) + rest) / 10);
				add[j] = ((((add[j] - '0') * 5) + k) % 10) + '0';
			}
			else
			{
				add[j] = (((add[j] - '0') * 5) + rest) + '0';
				rest = 0;
			}
			j--;
			if (rest != 0 && j < 0)
			{
				j = 0;
				while (add[j])
					j++;
				while (j > 0)
				{
					add[j] = add[j - 1];
					j--;
				}
				add[0] = (rest + '0');
				j = -1;
			}
		}
		i--;
	}
	add = ft_zero(ft_strrev(add), l);
	return (ft_add2(add, tab));
}

char	*ft_float2(unsigned long long bin, char *tab, int size, int m)
{
	char				add[5000];
	int					i;
	int					j;

	i = 0;
	j = (m == 1) ? 0 : size;
	if (m == 1)
	{
		while (j < size)
		{
			if (((bin >> j) & 1) == 1)
				tab = ft_mult(j, tab, add);
			ft_bzero(add, 5000);
			j++;
		}
	}
	else
	{
		while (j >= 0)
		{
			if (((bin >> j) & 1) == 1)
				tab = ft_mult2(i, tab, add);
			ft_bzero(add, 5000);
			j--;
			i++;
		}
	}
	return (tab);
}

void	ft_float(long double f, char *tab, int m)
{
	unsigned long long	*nb;
	unsigned long long	ent;
	unsigned long long	vir;
	int					p;

	nb = (unsigned long long*)&f;
	p = (nb[1] & 0x7FFF) - 16382;
	ent = nb[0] >> (64 - p);
	vir = (p < 0) ? ent : nb[0] << p;
	ent = (p < 0) ? 0 : ent;
	if (m == 1)
		tab = ft_float2(ent, tab, p + 1, 1);
	else
		tab = ft_float2(vir, tab, 63, 2);
	if (f < 0 && m == 1)
	{
		p = 0;
		while (tab[p])
			p++;
		while (p > 0)
		{
			tab[p] = tab[p - 1];
			p--;
		}
		tab[0] = '-';
	}
}
