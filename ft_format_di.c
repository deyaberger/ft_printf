/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/05/13 13:37:35 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_format_di(t_printf save, va_list ap, char *buf)
{
	int		i;

	i = save.flags;


