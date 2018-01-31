/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:11:11 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 19:10:48 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static unsigned char g_md5_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

t_md5 g_md5[64] = {
	{0, 1, 2, 3, 0, 7, 0xd76aa478},
	{3, 0, 1, 2, 1, 12, 0xe8c7b756},
	{2, 3, 0, 1, 2, 17, 0x242070db},
	{1, 2, 3, 0, 3, 22, 0xc1bdceee},
	{0, 1, 2, 3, 4, 7, 0xf57c0faf},
	{3, 0, 1, 2, 5, 12, 0x4787c62a},
	{2, 3, 0, 1, 6, 17, 0xa8304613},
	{1, 2, 3, 0, 7, 22, 0xfd469501},
	{0, 1, 2, 3, 8, 7, 0x698098d8},
	{3, 0, 1, 2, 9, 12, 0x8b44f7af},
	{2, 3, 0, 1, 10, 17, 0xffff5bb1},
	{1, 2, 3, 0, 11, 22, 0x895cd7be},
	{0, 1, 2, 3, 12, 7, 0x6b901122},
	{3, 0, 1, 2, 13, 12, 0xfd987193},
	{2, 3, 0, 1, 14, 17, 0xa679438e},
	{1, 2, 3, 0, 15, 22, 0x49b40821},
	{0, 1, 2, 3, 1, 5, 0xf61e2562},
	{3, 0, 1, 2, 6, 9, 0xc040b340},
	{2, 3, 0, 1, 11, 14, 0x265e5a51},
	{1, 2, 3, 0, 0, 20, 0xe9b6c7aa},
	{0, 1, 2, 3, 5, 5, 0xd62f105d},
	{3, 0, 1, 2, 10, 9, 0x2441453 },
	{2, 3, 0, 1, 15, 14, 0xd8a1e681},
	{1, 2, 3, 0, 4, 20, 0xe7d3fbc8},
	{0, 1, 2, 3, 9, 5, 0x21e1cde6},
	{3, 0, 1, 2, 14, 9, 0xc33707d6},
	{2, 3, 0, 1, 3, 14, 0xf4d50d87},
	{1, 2, 3, 0, 8, 20, 0x455a14ed},
	{0, 1, 2, 3, 13, 5, 0xa9e3e905},
	{3, 0, 1, 2, 2, 9, 0xfcefa3f8},
	{2, 3, 0, 1, 7, 14, 0x676f02d9},
	{1, 2, 3, 0, 12, 20, 0x8d2a4c8a},
	{0, 1, 2, 3, 5, 4, 0xfffa3942},
	{3, 0, 1, 2, 8, 11, 0x8771f681},
	{2, 3, 0, 1, 11, 16, 0x6d9d6122},
	{1, 2, 3, 0, 14, 23, 0xfde5380c},
	{0, 1, 2, 3, 1, 4, 0xa4beea44},
	{3, 0, 1, 2, 4, 11, 0x4bdecfa9},
	{2, 3, 0, 1, 7, 16, 0xf6bb4b60},
	{1, 2, 3, 0, 10, 23, 0xbebfbc70},
	{0, 1, 2, 3, 13, 4, 0x289b7ec6},
	{3, 0, 1, 2, 0, 11, 0xeaa127fa},
	{2, 3, 0, 1, 3, 16, 0xd4ef3085},
	{1, 2, 3, 0, 6, 23, 0x4881d05 },
	{0, 1, 2, 3, 9, 4, 0xd9d4d039},
	{3, 0, 1, 2, 12, 11, 0xe6db99e5},
	{2, 3, 0, 1, 15, 16, 0x1fa27cf8},
	{1, 2, 3, 0, 2, 23, 0xc4ac5665},
	{0, 1, 2, 3, 0, 6, 0xf4292244},
	{3, 0, 1, 2, 7, 10, 0x432aff97},
	{2, 3, 0, 1, 14, 15, 0xab9423a7},
	{1, 2, 3, 0, 5, 21, 0xfc93a039},
	{0, 1, 2, 3, 12, 6, 0x655b59c3},
	{3, 0, 1, 2, 3, 10, 0x8f0ccc92},
	{2, 3, 0, 1, 10, 15, 0xffeff47d},
	{1, 2, 3, 0, 1, 21, 0x85845dd1},
	{0, 1, 2, 3, 8, 6, 0x6fa87e4f},
	{3, 0, 1, 2, 15, 10, 0xfe2ce6e0},
	{2, 3, 0, 1, 6, 15, 0xa3014314},
	{1, 2, 3, 0, 13, 21, 0x4e0811a1},
	{0, 1, 2, 3, 4, 6, 0xf7537e82},
	{3, 0, 1, 2, 11, 10, 0xbd3af235},
	{2, 3, 0, 1, 2, 15, 0x2ad7d2bb},
	{1, 2, 3, 0, 9, 21, 0xeb86d391},
};

t_uchar	*md5_pad(t_uchar *old, int *old_len)
{
	t_uchar	*new;
	t_ulong	bit_length;
	int		new_len;

	bit_length = (t_ulong)*old_len * 8;
	new_len = *old_len + 8 + 64 - (*old_len + 8) % 64;
	new = (t_uchar *)ft_strnew(new_len);
	ft_memcpy(new, old, *old_len);
	ft_memcpy(new + *old_len, g_md5_padding, new_len - *old_len - 8);
	ft_memcpy(new + new_len - 8, &bit_length, 8);
	*old_len = new_len;
	free(old);
	return (new);
}

void	md5_round(t_uint *buffer, t_uint *x, int i)
{
	t_uint *a;
	t_uint b;
	t_uint c;
	t_uint d;

	a = &buffer[g_md5[i].a];
	b = buffer[g_md5[i].b];
	c = buffer[g_md5[i].c];
	d = buffer[g_md5[i].d];
	if (i < 16)
		*a += F(b, c, d) + x[g_md5[i].index] + g_md5[i].sin;
	else if (i < 32)
		*a += G(b, c, d) + x[g_md5[i].index] + g_md5[i].sin;
	else if (i < 48)
		*a += H(b, c, d) + x[g_md5[i].index] + g_md5[i].sin;
	else if (i < 64)
		*a += I(b, c, d) + x[g_md5[i].index] + g_md5[i].sin;
	*a = md5_rotate_left(*a, g_md5[i].shift);
	*a += b;
}

void	md5_process_block(t_uchar *block, t_uint *old_buffer)
{
	int		i;
	t_uint	x[16];
	t_uint	new_buffer[4];

	md5_str_to_int(x, block, 64);
	ft_memcpy(new_buffer, old_buffer, 16);
	i = 0;
	while (i < 64)
	{
		md5_round(new_buffer, x, i);
		i++;
	}
	old_buffer[0] += new_buffer[0];
	old_buffer[1] += new_buffer[1];
	old_buffer[2] += new_buffer[2];
	old_buffer[3] += new_buffer[3];
}

t_uint	*md5_init_buffer(void)
{
	t_uint *buffer;

	buffer = malloc(4 * sizeof(t_uint));
	buffer[0] = 0x67452301;
	buffer[1] = 0xefcdab89;
	buffer[2] = 0x98badcfe;
	buffer[3] = 0x10325476;
	return (buffer);
}

t_uint	*md5_calculate_hash(t_uchar *input, int len)
{
	int		i;
	t_uint	*buffer;

	buffer = md5_init_buffer();
	input = md5_pad(input, &len);
	i = 0;
	while (i < len / 64)
	{
		md5_process_block(input + i * 64, buffer);
		i++;
	}
	free(input);
	return (buffer);
}
