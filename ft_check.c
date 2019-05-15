/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:09:02 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/15 19:30:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check(t_printf save, int *j)
{
	if (*j == BUFF_SIZE)
		 write(1, save.buf, BUFF_SIZE);
	*j = 0;
}
