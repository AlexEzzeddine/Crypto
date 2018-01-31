/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:47:42 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 00:34:45 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_int_to_str(t_uchar *output, t_uint *input, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (t_uchar)(input[i] & 0xff);
		output[j + 1] = (t_uchar)((input[i] >> 8) & 0xff);
		output[j + 2] = (t_uchar)((input[i] >> 16) & 0xff);
		output[j + 3] = (t_uchar)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	sha256_str_to_int(t_uint *output, t_uchar *input, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = (((t_uint)input[j]) << 24)
					| (((t_uint)input[j + 1]) << 16)
					| (((t_uint)input[j + 2]) << 8)
					| ((t_uint)input[j + 3]);
		i++;
		j += 4;
	}
}

t_uint	sha256_rotate_left(t_uint x, int n)
{
	return (x << n) | (x >> (32 - n));
}

t_uint	sha256_rotate_right(t_uint x, int n)
{
	return (x >> n) | (x << (32 - n));
}

t_ulong	sha256_bswap_l(t_ulong x)
{
	return ((x & 0xff00000000000000ull) >> 56 |
			((x & 0x00ff000000000000ull) >> 40) |
			((x & 0x0000ff0000000000ull) >> 24) |
			((x & 0x000000ff00000000ull) >> 8) |
			((x & 0x00000000ff000000ull) << 8) |
			((x & 0x0000000000ff0000ull) << 24) |
			((x & 0x000000000000ff00ull) << 40) |
			((x & 0x00000000000000ffull) << 56));
}
