/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/26 18:56:21 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_flags(char *str, t_printf save, int *i)
{
	while (str[*i] && (str[*i] == '#' || str[*i] == '0' || str[*i] == '+'
			|| str[*i] == ' ' || str[*i] == '-'))
	{
		if (str[*i] == '#')
			save.flags = save.flags | F_HASH;
		else if (str[*i] == '0')
			save.flags = save.flags | F_ZERO;
		else if (str[*i] == '+')
			save.flags = save.flags | F_PLUS;
		else if (str[*i] == ' ')
			save.flags = save.flags | F_SPACE;
		else if (str[*i] == '-')
			save.flags = save.flags | F_MINUS;
		*i += 1;
	}
	return (save);
}

int			ft_width(char *str, t_printf *save, int *i)
{
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			save->width = (save->width * 10) + (str[*i] - '0');
			*i += 1;
		}
	}
	if (str[*i] == '.')
	{
		save->flags |= F_POINT;
		*i += 1;
		while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
		{
			save->precision = (save->precision * 10) + (str[*i] - '0');
			*i += 1;
		}
	}
	return (1);
}

int			ft_modif(char *str, t_printf *save, int *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
	{
		save->modif = save->modif | M_HH;
		*i += 1;
	}
	else if (str[*i] == 'h' && str[*i + 1] != 'h')
		save->modif = save->modif | M_H;
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
	{
		save->modif = save->modif | M_LL;
		*i += 1;
	}
	else if (str[*i] == 'l' && str[*i + 1] != 'l')
		save->modif = save->modif | M_L;
	else if (str[*i] == 'L')
		save->modif = save->modif | M_BIGL;
	if (str[*i] == 'h' || str[*i] == 'l' || str[*i] == 'L')
		*i += 1;
	if (str[*i] != 'd' && str[*i] != 'i' && str[*i] != 'o' && str[*i] != 'u'
			&& str[*i] != 'x' && str[*i] != 'X' && str[*i] != 'f'
			&& str[*i] != 'c' && str[*i] != 's' && str[*i] != 'p')
		return (0);
	return (1);
}

t_printf	ft_format(char c, t_printf save, va_list ap, int *j)
{
	if (c == 'c' || c == 's' || c == 'p')
		save = ft_format_csp(save, ap, j, c);
	else if (c == 'd' || c == 'i')
		save = ft_format_di(save, ap, j);
	else if (c == 'x' || c == 'X')
		save = ft_format_xx(save, ap, j, c);
	else if (c == 'f')
		save = ft_format_f(save, ap, j);
	else if (c == 'o' || c == 'u')
		save = ft_format_ou(save, ap, j, c);
	else if (c == '%')
		save = ft_format_pct(save, j);
	return (save);
}

t_printf	ft_convert(t_printf save, char *str, va_list ap, int *j)
{
	int		i;
//	int		k;

	i = 0;
//	k = i;
	save.flags = 0;
	save.width = 0;
	save.precision = 0;
	save.modif = 0;
	save.index = 1;
	save = ft_flags(str, save, &i);
/*	while (str[i] && (str[i] != 'd' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u'
				&& str[i] != 'x' && str[i] != 'X' && str[i] != 'f'
				&& str[i] != 'c' && str[i] != 's' && str[i] != 'p'))
	{
		save = ft_flags(str, save, &i);
		ft_width(str, &save, &i);
		ft_modif(str, &save, &i);
		if (i == k)
			i++;
	} NE MARCHE PAS AVEC 42FILE CHECKER...MEME SI CA MARCHE AVEC MES TESTS*/
	ft_width(str, &save, &i);
	ft_modif(str, &save, &i);
	if (ft_width(str, &save, &i) == 0 && ft_modif(str, &save, &i) == 0)
	{
		if (str[i] == '%' && str[i - 1] == '%')
			save = ft_check_add(save, j, '%');
		i = 0;
		while (str[i] && (str[i] == '%' || str[i] == ' ' || str[i] == 'h'
					|| str[i] == 'l' || str[i] == 'L'))
		{
			save.index += 1;
			i++;
		}
		return (save);
	}
	save.index = i + 2;
	save = ft_format(str[i], save, ap, j);
	return (save);
}
