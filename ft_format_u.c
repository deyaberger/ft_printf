/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:40:58 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/14 19:24:58 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		ft_format_u(t_printf save, va_list ap, int *j, char c)
{
	(void)ap;
	(void)*j;
	(void)c;
	return (save);
}
