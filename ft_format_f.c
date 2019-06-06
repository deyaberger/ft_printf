/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/06/06 11:59:56 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_w_add_f(t_printf save, int *j, int count, char *fix, char *nb)
{
	long	s;
	int		w;

	w = save.width;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre == 6))
		s = ft_strlen(fix) + 7;
	else
		s = ft_strlen(fix) + save.pre + 1;
	if (fix[0] == '-' && save.pre > 0 && save.pre < s && w > s)
		count++;
	if (fix[0] == '-' && (save.flags & F_ZERO) && !(save.flags & F_MINUS)
		&& !(save.pre))
		save = ft_check_add(save, j, '-');
	if ((save.flags & F_ZERO) && !(save.pre) && !(save.flags & F_MINUS)
		&& !(save.flags & F_POINT))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	if (fix[0] == '0' && nb[0] == '0' && !(save.pre) && save.flags & F_POINT)
		save = ft_check_add(save, j, ' ');
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_width_f(t_printf save, int *j, char *fix, char *nb)
{
	int		count;
	long	s;
	int		w;

	w = save.width;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre == 6))
		s = ft_strlen(fix) + 7;
	else
		s = ft_strlen(fix) + save.pre + 1;
	count = w - s;
	if (save.pre && w > save.pre && s < save.pre)
		count = w - save.pre;
	if (save.pre && s < save.pre && w <= save.pre)
		return (save);
	if (save.flags & F_PLUS && fix[0] != '-')
	{
		if (save.flags & F_ZERO && !(save.flags & F_MINUS) && !(save.pre))
			save = ft_check_add(save, j, '+');
		count--;
	}
	if ((fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		|| (fix[0] == '-' && save.pre))
		count--;
	save = ft_w_add_f(save, j, count, fix, nb);
	return (save);
}


t_printf	ft_pre_f(t_printf save, int *j, char *fix, char *nb)
{
	long	s;
	int		p;

	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre == 6))
		s = ft_strlen(fix) + 7;
	else
		s = ft_strlen(fix) + save.pre + 1;
	p = save.pre;
	if (fix[0] != '-' && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	if (s < p)
	{
		while (p - s > 0)
		{
			save = ft_check_add(save, j, '0');
			p--;
		}
	}
	if (fix[0] == '0' && nb[0] == '0' && save.pre > 0)
		save = ft_check_add(save, j, '0');
	return (save);
}

t_printf	ft_format_f(t_printf save, va_list ap, int *j)
{
	char	*fix;
	char 	*fix2;
	char	*nb;
	char	*nb2;	

	(void)ap;
	fix2 = "6";
	fix = ft_strdup(fix2);
	nb2 = "62399999999999966604491419275291264057159423828125";
	nb = ft_strdup(nb2);
	if (fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		save = ft_check_add(save, j, ' ');
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_f(save, j, fix, nb);
	if (save.pre)
		save = ft_pre_f(save, j, fix, nb);
	save = ft_ftoa(save, j, fix, nb);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_f(save, j, fix, nb);
	return (save);
}
