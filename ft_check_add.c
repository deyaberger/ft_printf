/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:37:21 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/22 16:39:36 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_check_add(t_printf save, int *j, char c)
{
	if (*j == BUFF_SIZE && (*j = 0) == 0)
		 write(1, &save.buf, BUFF_SIZE);
	save.buf[*j] = c;
	*j += 1;
	return (save);
}
