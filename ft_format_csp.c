/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:37:05 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/23 11:15:28 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_form_c(t_printf save, int *j, char c)
{
	int		i;

	i = 0;
	if (save.flags == 4)
	{
		save = ft_check_add(save, j, c);
		i++;
	}
	else
		save.width--;
	while (i < save.width)
	{
		save = ft_check_add(save, j, ' ');
		i++;
	}
	if (save.flags == 0)
		save = ft_check_add(save, j, c);
	return (save);
}

t_printf	ft_print(t_printf save, int *j, char *str, int *i)
{
	while (str[*i] && *i != save.precision)
	{
		save = ft_check_add(save, j, str[*i]);
		*i += 1;
	}
	return (save);
}

t_printf	ft_form_s(t_printf save, int *j, char *str)
{
	int		i;

	i = 0;
	if ((save.flags & F_POINT) != F_POINT)
		save.precision = -1;
	if ((save.flags & F_MINUS) == F_MINUS)
		save = ft_print(save, j, str, &i);
	if (save.precision >= 0)
		save.width -= (ft_strlen(str) - (ft_strlen(str) - save.precision));
	else
		save.width -= ft_strlen(str);
	i = 0;
	while (i++ < save.width)
		save = ft_check_add(save, j, ' ');
	i = 0;
	if ((save.flags & F_MINUS) != F_MINUS)
		save = ft_print(save, j, str, &i);
	return (save);
}

t_printf	ft_form_p(t_printf save, int *j, void *p)
{
	int					i;
	unsigned long int	k;
	int					s;

	k = (unsigned long int)p;
	i = 63;
	while ((k >> i | k >> (i - 1) | k >> (i - 2) | k >> (i - 3)) == 0)
		i -= 4;
	while (i % 4 != 0)
		i++;
	s = (save.width - ((i / 4) + 2));
	s < 0 ? s = 0 : 0;
	i--;
	if (save.width == 0)
		save = ft_dtoh(save, j, k, i);
	if (save.width != 0 && (save.flags & F_MINUS) == F_MINUS)
		save = ft_dtoh(save, j, k, i);
	while (s-- != 0)
		save = ft_check_add(save, j, ' ');
	if (save.width != 0 && (save.flags & F_MINUS) != F_MINUS)
		save = ft_dtoh(save, j, k, i);
	return (save);
}

t_printf	ft_format_csp(t_printf save, va_list ap, int *j, char c)
{
	int		a;
	char	*str;
	void	*p;

	if (c == 'c')
	{
		a = va_arg(ap, int);
		save = ft_form_c(save, j, a);
	}
	else if (c == 's')
	{
		str = va_arg(ap, char*);
		save = ft_form_s(save, j, str);
	}
	else if (c == 'p')
	{
		p = va_arg(ap, void*);
		save = ft_form_p(save, j, p);
	}
	return (save);
}
