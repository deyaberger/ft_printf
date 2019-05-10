/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:04:24 by dberger           #+#    #+#             */
/*   Updated: 2019/05/10 18:09:32 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFF_SIZE 5555

# define F_SPACE	(1 << 0)
# define F_HASH		(1 << 1)
# define F_MINUS	(1 << 2)
# define F_PLUS		(1 << 3)
# define F_ZERO		(1 << 4)

# define M_HH		(1 << 10) 
# define M_H		(1 << 11) 
# define M_L		(1 << 12) 
# define M_BIGL		(1 << 13) 
# define M_LL		(1 << 14)

typedef struct		s_printf
{
	int				flags;
	int				width;
	int				precision;
	int				modif;
	int				type;
	char			buf[BUFF_SIZE];
}					t_printf;

#endif
