/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizenb_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:33:42 by dberger           #+#    #+#             */
/*   Updated: 2019/05/15 18:33:49 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_sizenb_ll(long long n)
{
	long long	i;
	long long	nb;

	i = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i++);
}
