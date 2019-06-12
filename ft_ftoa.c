/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 08:43:36 by dberger           #+#    #+#             */
/*   Updated: 2019/06/12 16:17:56 by dberger          ###   ########.fr       */
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

char		*ft_n_round(char *str, int n, t_printf *save)
{
	int		ret;

	ret = 0;
	if (save->min != 3 || (save->min == 3 && (str[n] == '1'
		|| str[n] == '3' || str[n] == '5' || str[n] == '7' || str[n] == '9')))
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
		if (str[n] > '9' && (save->min != 1 || (save->min == 1 && n != 0)))
			str = ft_increase(str, n);
		if (str[n] > '9' && save->min == 1 && n == 0 && (save->min = 2) == 2)
			str[n] = '0';
	}
	return (str);
}

char		*ft_nb(t_printf *save, char *nb, int *p)
{
	int		i;
	int		s;

	s = ft_strlen(nb);
	i = 0;
	save->min = 1;
	if ((!(save->pre) && !(save->flags & F_POINT)))
		*p = 6;
	while (s < *p || s < 6)
		nb[s++] = '0';
	nb[s] = '\0';
	while (*p > ft_strlen(nb) && *p > 0 && nb[*p] == '0')
		*p -= 1;
	if (*p > 0 && (nb[*p] >= '5'))
		nb = ft_n_round(nb, (*p - 1), save);
	if (nb[0] == '0')
	{
		while (i < *p)
			nb[i++] = '0';
		nb[i] = '\0';
	}
	return (nb);
}

char		*ft_zerofix(char *fix)
{
	int		i;
	char	c;

	i = 0;
	c = fix[0];
	if ((fix[0] != '-' && fix[0] == '0' && fix[1] != '\0')
			|| (fix[0] == '-' && fix[1] == '0' && fix[2] != '\0'))
	{
		if (fix[0] == '-')
			i++;
		while (i < (int)ft_strlen(fix) && fix[i])
		{
			c = fix[i + 1];
			fix[i] = fix[i + 1];
			fix[i + 1] = c;
			i++;
		}
		fix[i] = '\0';
	}
	return (fix);
}

t_printf	ft_ftoa(t_printf save, int *j, char *fix, char *nb)
{
	int		i;
	int		p;
	int		f;

	p = save.pre;
	i = 0;
	f = save.flags;
	fix = ft_zerofix(fix);
	if (ft_strlen(fix) > 0 && !(save.pre) && (f & F_POINT) && nb[0] >= '5')
	{
		(save.min = (nb[0] == '5' && nb[1] == '\0') ? 3 : save.min);
		fix = ft_n_round(fix, (ft_strlen(fix) - 1), &save);
	}
	nb = ft_nb(&save, nb, &p);
	if (save.min == 2)
		fix = ft_n_round(fix, (ft_strlen(fix) - 1), &save);
	if (fix[0] == '-' && (save.width) && (f & F_ZERO) && !(f & F_MINUS))
		i = 1;
	while (fix[i])
		save = ft_check_add(save, j, fix[i++]);
	i = 0;
	if ((!(save.pre) && !(f & F_POINT)) || (save.pre > 0) || (f & F_HASH))
	{
		save = ft_check_add(save, j, '.');
		if ((!(save.pre) && !(f & F_POINT)) || (save.pre > 0))
			while (nb[i] && i < p)
				save = ft_check_add(save, j, nb[i++]);
	}
	return (save);
}
