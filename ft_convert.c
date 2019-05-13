/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/13 13:37:32 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert(char *str, va_list ap, char *buf)
{
	int			i;
	t_printf 	save;

	i = 0;
	if (!(save = (t_printf)malloc(sizeof(t_printf))))
		return (NULL);
	save.flags = 0;
	save.width = 0;
	save.precision = 0;
	save.modif = 0;
	i++;
	while (str[i] != d && str[i] != i && str[i] && str[i] != o && str[i] != u 
		&& str[i] != x && str[i] != X && str[i] != f && str[i] != c && str[i] != s
		&& str[i] != p)
	{
		if (str[i] == '#')
			save.flags = save.flgas | F_HASH;
		if (str[i] == '0')
			save.flags = save.flags | F_ZERO;
		if (str[i] == '+')
			save.flags = save.flags | F_MINUS;
		if (str[i] == ' ')
			save.flags = save.flags | F_SPACE;
		if (str[i] == '-')
			save.flags = save.flags | F_MINUS;
		i++;
	}
	if (str[i] == 'd')
	buf = ft_format_di(save, ap, buf);
	return ("RESULTAT");
}
