/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/22 12:14:19 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_flags(char *str, t_printf save, int *i)
{
	while (str[*i] == '#' || str[*i] == '0' || str[*i] == '+'
			|| str[*i] == ' ' || str[*i] == '-')
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
	char	res[1];

	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			res[0] = str[*i];
			save->width = (save->width * 10) + ft_atoi(res);
			*i += 1;
		}
	}
	if (str[*i] == '.')
	{
		*i += 1;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			res[0] = str[*i];
			save->precision = (save->precision * 10) + ft_atoi(res);
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
		save = ft_format_xX(save, ap, j, c);
	else if (c == 'f')
		save = ft_format_f(save, ap, j, c);
	else if (c == 'o')
		save = ft_format_o(save, ap, j, c);
	else if (c == 'u')
		save = ft_format_u(save, ap, j, c);
	return (save);
}

t_printf	ft_convert(t_printf save, char *str, va_list ap, int *j)
{
	int		i;

	i = 0;
	save = ft_flags(str, save, &i);
	if (ft_width(str, &save, &i) == 0 || ft_modif(str, &save, &i) == 0)
	{
		ft_check(save, j);
		save.buf[*j] = '%';
		save.index = 1;
		*j += 1;
		return (save);
	}
	save.index = i + 2;
	save = ft_format(str[i], save, ap, j);
	return (save);
}
