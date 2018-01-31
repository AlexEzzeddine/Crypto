/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:46:47 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 02:20:01 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "sha256_ops.h"

static unsigned char g_sha256_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

t_uint g_sha256_k[64] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

t_uchar	*sha256_pad(t_uchar *old, int *old_len)
{
	t_uchar	*new;
	t_ulong	bit_length;
	int		new_len;

	bit_length = sha256_bswap_l((t_ulong)*old_len * 8);
	new_len = *old_len + 8 + 64 - (*old_len + 8) % 64;
	new = (t_uchar *)ft_strnew(new_len);
	ft_memcpy(new, old, *old_len);
	ft_memcpy(new + *old_len, g_sha256_padding, new_len - *old_len - 8);
	ft_memcpy(new + new_len - 8, &bit_length, 8);
	*old_len = new_len;
	free(old);
	return (new);
}

void	sha256_round(t_uint *m, t_uint *w, int i)
{
	t_uint t1;
	t_uint t2;

	t1 = m[7] + EP1(m[4]) + CH(m[4], m[5], m[6]) + g_sha256_k[i] + w[i];
	t2 = EP0(m[0]) + MA(m[0], m[1], m[2]);
	m[7] = m[6];
	m[6] = m[5];
	m[5] = m[4];
	m[4] = m[3] + t1;
	m[3] = m[2];
	m[2] = m[1];
	m[1] = m[0];
	m[0] = t1 + t2;
}

void	sha256_fill_words(t_uint *w)
{
	int		i;
	t_uint	s0;
	t_uint	s1;

	i = 16;
	while (i < 64)
	{
		s0 = ROTR(w[i - 15], 7) ^ ROTR(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = ROTR(w[i - 2], 17) ^ ROTR(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
}

void	sha256_process_block(t_uchar *block, t_uint *old_buffer)
{
	int		i;
	t_uint	w[64];
	t_uint	new_buffer[8];

	sha256_str_to_int(w, block, 64);
	sha256_fill_words(w);
	ft_memcpy(new_buffer, old_buffer, 32);
	i = 0;
	while (i < 64)
	{
		sha256_round(new_buffer, w, i);
		i++;
	}
	old_buffer[0] += new_buffer[0];
	old_buffer[1] += new_buffer[1];
	old_buffer[2] += new_buffer[2];
	old_buffer[3] += new_buffer[3];
	old_buffer[4] += new_buffer[4];
	old_buffer[5] += new_buffer[5];
	old_buffer[6] += new_buffer[6];
	old_buffer[7] += new_buffer[7];
}

t_uint	*sha256_init_buffer(void)
{
	t_uint *buffer;

	buffer = malloc(8 * sizeof(t_uint));
	buffer[0] = 0x6A09E667;
	buffer[1] = 0xBB67AE85;
	buffer[2] = 0x3C6EF372;
	buffer[3] = 0xA54FF53A;
	buffer[4] = 0x510E527F;
	buffer[5] = 0x9B05688C;
	buffer[6] = 0x1F83D9AB;
	buffer[7] = 0x5BE0CD19;
	return (buffer);
}
