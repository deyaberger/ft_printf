/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 08:43:36 by dberger           #+#    #+#             */
/*   Updated: 2019/06/07 11:48:59 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_n_round(char *str, int n)
{
	int		ret;
	char 	c;

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
			{
				ret = 0;
			}
		}
		if (str[n] > '9')
		{
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
		}
	}
	return (str);
}

char		*ft_fix_nb(t_printf save, char *fix, char *nb, int mode)
{
	int		s;
	int		p;
	int		i;
	int		z;

	s = ft_strlen(fix);
	p = save.pre;
	z = save.width;
	i = 0;
	if (s > 0)
		s--;
	if ((!(save.pre) && !(save.flags & F_POINT)))
		p = 6;
	if (mode == 1 && nb[0] >= '5' && !(save.pre) && (save.flags & F_POINT))
		fix = ft_n_round(fix, s);
	if (mode == 2)
	{
		if (nb[p] >= '5' && p >= 1)
			nb = ft_n_round(nb, (p - 1));
		if (nb[0] == '0')
		{
			while (i < p)
			{
				nb[i] = '0';
				nb[i + 1] = '\0';
				i++;
			}
		}
	}
	return (mode == 1 ? fix : nb);
}

t_printf	ft_ftoa(t_printf save, int *j, char *fix, char *nb)
{
	int 	i;
	int		p;
	int		s;

	p = save.pre;
	i = 0;
	s = ft_strlen(nb);
	if (nb[0] == '\0')
	{
		nb[0] = '0';
		nb[1] = '\0';
	}
	if (fix[0] == '\0')
	{
		fix[0] = '0';
		fix[1] = '\0';
	}
	fix = ft_fix_nb(save, fix, nb, 1);
	if (fix[0] == '-' && (save.width) && (save.flags & F_ZERO))
		i = 1;
	while (fix[i])
	{
		save = ft_check_add(save, j, fix[i]);
		i++;
	}
	i = 0;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre > 0) 
		|| (save.flags & F_HASH))
	{
		save = ft_check_add(save, j, '.');
		if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre > 0))
		{
			nb = ft_fix_nb(save, fix, nb, 2);
			while (s < p || s < 6)
			{
				nb[s] = '0';
				nb[s + 1] = '\0';
				s++;
			}
			nb[s] = '\0';
			if ((!(save.pre) && !(save.flags & F_POINT)))
				p = 6;
			while (nb[i] && i < p)
			{
				save = ft_check_add(save, j, nb[i]);
				i++;
			}
		}
	}
	return (save);
}
