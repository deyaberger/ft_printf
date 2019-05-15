/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:37:05 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/15 15:06:23 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_form_c(t_printf save, int *j, char c)
{
	int		i;

	i = 0;
	if (save.flags != 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write(1, save.buf, BUFF_SIZE);
		save.buf[*j] = c;
		*j += 1;
	}
	while (i++ < save.width - 1)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write(1, save.buf, BUFF_SIZE);
		save.buf[*j] = ' ';
		*j += 1;
	}
	if (save.flags == 0)
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			write(1, save.buf, BUFF_SIZE);
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

	(void)*j;
	i = 0;
	printf("len : [%s]\n", (char*)&p);
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
