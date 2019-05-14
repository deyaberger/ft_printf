/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:38:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/14 19:24:31 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		ft_format_f(t_printf save, va_list ap, int *j, char c)
{
	(void)ap;
	(void)*j;
	(void)c;
	return (save);
}
