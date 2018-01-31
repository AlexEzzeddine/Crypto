/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:47:42 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 01:54:32 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void	sha512_long_to_str(t_uchar *output, t_ulong *input, int len)
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
		output[j + 4] = (t_uchar)((input[i] >> 32) & 0xff);
		output[j + 5] = (t_uchar)((input[i] >> 40) & 0xff);
		output[j + 6] = (t_uchar)((input[i] >> 48) & 0xff);
		output[j + 7] = (t_uchar)((input[i] >> 56) & 0xff);
		i++;
		j += 8;
	}
}

void	sha512_str_to_long(t_ulong *output, t_uchar *input, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = (((t_ulong)input[j]) << 56)
					| (((t_ulong)input[j + 1]) << 48)
					| (((t_ulong)input[j + 2]) << 40)
					| (((t_ulong)input[j + 3]) << 32)
					| (((t_ulong)input[j + 4]) << 24)
					| (((t_ulong)input[j + 5]) << 16)
					| (((t_ulong)input[j + 6]) << 8)
					| ((t_ulong)input[j + 7]);
		i++;
		j += 8;
	}
}

t_uint	sha512_rotate_left(t_uint x, int n)
{
	return (x << n) | (x >> (32 - n));
}

t_uint	sha512_rotate_right(t_uint x, int n)
{
	return (x >> n) | (x << (32 - n));
}

t_ulong	sha512_bswap_l(t_ulong x)
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
