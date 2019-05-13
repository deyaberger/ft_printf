/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/13 19:42:09 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_convert(t_printf save, char *str, va_list ap, int *j)
{
	int	type;
	int		i;

	i = 0;
	if (*j == BUFF_SIZE && (*j = 0) == 0)
		printf("%s", save.buf);
	if (str[i] == 'd')
		save = ft_format_di(save, ap, j);
	return (save);
}
