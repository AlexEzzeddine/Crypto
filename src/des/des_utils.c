/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 02:09:39 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 02:09:59 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

t_ulong	string_to_long64(t_uchar *str)
{
	t_ulong	n;
	int		i;

	n = 0;
	i = 0;
	while (i < 8)
	{
		n += ((t_ulong)(str[i])) << ((7 - i) * 8);
		i++;
	}
	return (n);
}

void	long64_to_string(t_uchar *str, t_ulong n)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		str[i] = (t_uchar)(n >> ((7 - i) * 8));
		i++;
	}
}

int		get_bit(t_ulong buf, t_ulong bit)
{
	return (buf >> (63 - bit)) & 1UL;
}

void	set_bit(t_ulong *buf, t_ulong bit)
{
	*buf |= (1UL << (63 - bit));
}
