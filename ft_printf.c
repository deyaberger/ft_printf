/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:54 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/13 11:37:44 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_add_result(char *buf, char *res, int *j)
{
	int		i;

	i = 0;
	while (res[i] != '\0')
	{
		if (*j == BUFF_SIZE && (*j = 0) == 0)
			printf("%s", buf);
		buf[*j] = res[i];
		i++;
		*j = *j + 1;
	}
	return (buf);
}

void	ft_process(char *buf, const char *restrict format, va_list ap)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (format[i])
	{
		while (format[i] && format[i] != '%')
		{
			if (j == BUFF_SIZE && (j = 0) == 0)
				printf("%s", buf);
			buf[j] = format[i];
			i++;
			j++;
		}
		if (format[i] == '%')
		{
			buf = ft_add_result(buf, ft_convert((char*)&format[i], ap), &j);
			i++;
		}
	}
	buf[j] = '\0';
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	char	buf[BUFF_SIZE + 1];

	va_start(ap, format);
	buf[BUFF_SIZE] = '\0';
	ft_process(buf, format, ap);
	printf("%s\n", buf);
	va_end(ap);
	return (0);
}
