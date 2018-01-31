/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_hex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 02:12:46 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 02:13:01 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

t_ulong	char_to_hex_digit(char c)
{
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (c - '0');
}

t_ulong	convert_hex_to_bits(char *key)
{
	t_ulong	k;
	int		i;

	k = 0;
	i = 0;
	while (i < 16)
	{
		k += (char_to_hex_digit(key[i]) << (4 * (15 - i)));
		i++;
	}
	return (k);
}
