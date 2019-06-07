/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 08:43:36 by dberger           #+#    #+#             */
/*   Updated: 2019/06/07 14:24:53 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_increase(char *str, int n)
{
	char	c;

	str[n] = '1';
	c = str[n + 1];
	str[n + 1] = '0';
	n = 2;
	while (str[n])
	{
		str[n] = c;
		if (n < ((int)ft_strlen(str) - 1))
			c = str[n + 1];
		n++;
	}
	str[n] = c;
	str[n + 1] = '\0';
	return (str);
}

char		*ft_n_round(char *str, int n)
{
	int		ret;

	ret = 0;
	str[n + 1] = '\0';
	str[n] += 1;
	if (str[n] > '9')
	{
		ret = 1;
		while (ret > 0 && n > 0 && str[n] > '9')
		{
			str[n] = '0';
			str[n - 1] += 1;
			n--;
			if (str[n] < '9')
				ret = 0;
		}
		if (str[n] > '9')
			str = ft_increase(str, n);
	}
	return (str);
}

char		*ft_nb(t_printf save, char *nb, int *p)
{
	int		i;
	int		s;

	s = ft_strlen(nb);
	i = 0;
	if ((!(save.pre) && !(save.flags & F_POINT)))
		*p = 6;
	if (nb[*p] >= '5' && *p >= 1)
		nb = ft_n_round(nb, (*p - 1));
	if (nb[0] == '0')
	{
		while (i < *p)
			nb[i++] = '0';
		nb[i] = '\0';
	}
	while (s < *p || s < 6)
		nb[s++] = '0';
	nb[s] = '\0';
	return (nb);
}

t_printf	ft_ftoa(t_printf save, int *j, char *fix, char *nb)
{
	int		i;
	int		p;

	p = save.pre;
	i = 0;
	if (ft_strlen(fix) > 0 && nb[0] >= '5' && !(save.pre)
			&& (save.flags & F_POINT))
		fix = ft_n_round(fix, (ft_strlen(fix) - 1));
	if (fix[0] == '-' && (save.width) && (save.flags & F_ZERO))
		i = 1;
	while (fix[i])
		save = ft_check_add(save, j, fix[i++]);
	i = 0;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre > 0)
			|| (save.flags & F_HASH))
	{
		save = ft_check_add(save, j, '.');
		if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre > 0))
		{
			nb = ft_nb(save, nb, &p);
			while (nb[i] && i < p)
				save = ft_check_add(save, j, nb[i++]);
		}
	}
	return (save);
}
