/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/13 19:45:55 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_flags(char *str, t_printf save, int *i)
{
	if (str[*i] == '#')
		save.flags = save.flags | F_HASH;
	else if (str[*i] == '0')
		save.flags = save.flags | F_ZERO;
	else if (str[*i] == '+')
		save.flags = save.flags | F_MINUS;
	else if (str[*i] == ' ')
		save.flags = save.flags | F_SPACE;
	else if (str[*i] == '-')
		save.flags = save.flags | F_MINUS;
	while (str[*i] != '#' && str[*i] != '0' && str[*i] != '+'
			&& str[*i] != ' ' && str[*i] != '-')
		*i += 1;
}

int			ft_width(char *str, t_printf save, int *i)
{
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			save.width = (save.width * 10) + ft_atoi((char*)str[*i]);
			*i += 1;
		}
	}
	if (str[*i] == '.')
	{
		*i += 1;
		if ((str[*i] <= '0' || str[*i] >= '9') && str[*i] != 'd'
				&& str[*i] != 'i' && str[*i] != 'o' && str[*i] != 'u'
				&& str[*i] != 'x' && str[*i] != 'X' && str[*i] != 'f'
				&& str[*i] != 'c' && str[*i] != 's' && str[*i] != 'p')
			return (0);
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			save.precision = (save.precision * 10) + ft_atoi((char*)str[*i]);
			*i += 1;
		}
	}
}

int			ft_modif(char *str, t_printf save, int *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
	{
		save.modif = save.modif | M_HH;
		*i += 1;
	}
	else if (str[*i] == 'h' && str[*i + 1] != 'h')
		save.modif = save.modif | M_H;
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
	{
		save.modif = save.modif | M_LL;
		*i += 1;
	}
	else if (str[*i] == 'l' && str[*i + 1] != 'l')
		save.modif = save.modif | M_L;
	else if (str[*i] == 'L')
		save.modif = save.modif | M_BIGL;
	*i += 1;
	if (str[*i] != 'd' && str[*i] != 'i' && str[*i] != 'o' && str[*i] != 'u'
			&& str[*i] != 'x' && str[*i] != 'X' && str[*i] != 'f'
			&& str[*i] != 'c' && str[*i] != 's' && str[*i] != 'p')
		return (0);
}

void		ft_format(char c, t_printf save, va_list, int *j)
{
	if (c == 'c' || c == 's' || c == 'p')
		ft_format_csp(save, ap, j);
	else if (c == 'd' || c == 'i')
		ft_format_di(save, ap, j);
	else if (c == 'x' || c == 'X')
		ft_format_xX(save, ap, j);
	else if (c == 'f')
		ft_format_f(save, ap, j);
	else if (c == 'o')
		ft_format_o(save, ap, j);
	else if (c == 'u')
		ft_format_u(save, ap, j);
}

t_printf	ft_convert(t_printf save, char *str, va_list ap, int *j)
{
	int			i;
	t_printf	save;

	i = 0;
	save.flags = 0;
	save.width = 0;
	save.precision = 0;
	save.modif = 0;
	i++;
	ft_flags(str, save, *i);
	if (ft_width(str, save, *i) == 0 || ft_modif(str, save, *i) == 0)
	{
		save.buf[j] = '%';
		*j += 1;
		return (save);
	}
	save.index = i + 1;
	ft_format(str[i], save, ap, *j);
	return (save);
}
