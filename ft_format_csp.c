/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:37:05 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/15 19:19:35 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_form_c(t_printf save, int *j, char c)
{
	int		i;

	i = 0;
	if (save.flags != 0)
	{
		ft_check(save, j);
		save.buf[*j] = c;
		*j += 1;
	}
	while (i++ < save.width - 1)
	{
		ft_check(save, j);
		save.buf[*j] = ' ';
		*j += 1;
	}
	if (save.flags == 0)
	{
		ft_check(save, j);
		save.buf[*j] = c;
		*j += 1;
	}	
	return (save);
}

t_printf	ft_form_s(t_printf save, int *j, char *str)
{
	(void)*j;
	(void)str;
	return (save);
}

t_printf	ft_form_p(t_printf save, int *j, void *p)
{
	int		i;

	i = 0;
	(void)*j;
	(void)p;
	/if (save.flags != 0)
	{
		ft_check(save, j);
		save = ft_deci_exa((unsigned long int)p, save, j);
		*j += 1;
	}
	while (i++ < save.width - 1)
	{
		ft_check(save, j);
		save.buf[*j] = ' ';
		*j += 1;
	}
	if (save.flags == 0)
	{
		ft_check(save, j);
		save.buf[*j] = c;
		*j += 1;
	}	
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
