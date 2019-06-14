/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:26:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/13 17:33:46 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char    *ft_strrev(char *str)
{
	int length;
	int i;
	int swap;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	length--;
	i = 0;
	while (i < length)
	{
		swap = str[i];
		str[i] = str[length];
		str[length] = swap;
		length--;
		i++;
	}
	return (str);
}

void    ft_bzero(void *s, size_t n)
{
	int i;

	i = 0;
	while (i != (int)n && n)
	{
		((char*)s)[i] = 0;
		i++;
	}
}

char    *ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

char    *ft_add(char *add, char *tab)
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
		if (rest != 0 && j < 0)
		{
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

char    *ft_mult(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;
	int		l;

	l = i;
	ft_bzero(add, 2048);
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
	return (ft_add(add, tab));
}

char    *ft_mult2(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;
	int		l;

	l = i;
	ft_bzero(add, 2048);
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
	return (ft_add(add, tab));
}

char	*ft_float2(unsigned long long bin, char *tab, int size, int m)
{
	char				add[2048];
	int					i;
	int					j;

	i = 0;
	j = (m == 1) ? 0 : size;
	ft_bzero(tab, 2048);
	if (m == 1)
	{
		while (j <= size)
		{
			if (((bin >> j) & 1) == 1)
				tab = ft_mult(j, tab, add);
			ft_bzero(add, 2048);
			j++;
		}
	}
	else
	{
		while (j >= 0)
		{
			if (((bin >> j) & 1) == 1)
				tab = ft_mult2(i, tab, add);
			ft_bzero(add, 2048);
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
	vir = nb[0] << p;
	if (m == 1)
		tab = ft_float2(ent, tab, p + 1, 1);
	else
		tab = ft_float2(vir, tab, 63, 2);
}

int		main(int argc, char **argv)
{
	char	tab1[2048];
	char	tab2[2048];
	float	f;

	f = strtof(argv[1], NULL);
	ft_float(f, tab1, 1);
	ft_float(f, tab2, 2);
	(void)argc;
	printf("[%s.%s]\n", tab1, tab2);
	printf("[%.70f]\n", strtof(argv[1], NULL));
	return (0);
}
