/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:46:47 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:35:04 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"
#include "sha512_ops.h"

static unsigned char g_sha512_padding[128] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

t_ulong g_sha512_k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

t_uchar	*sha512_pad(t_uchar *old, int *old_len)
{
	t_uchar	*new;
	t_ulong	bit_length;
	int		new_len;

	bit_length = sha512_bswap_l((t_ulong)*old_len * 8);
	new_len = *old_len + 16 + 128 - (*old_len + 16) % 128;
	new = (t_uchar *)ft_strnew(new_len);
	ft_memcpy(new, old, *old_len);
	ft_memcpy(new + *old_len, g_sha512_padding, new_len - *old_len - 16);
	ft_memcpy(new + new_len - 8, &bit_length, 8);
	*old_len = new_len;
	free(old);
	return (new);
}

void	sha512_round(t_ulong *m, t_ulong *w, int i)
{
	t_ulong t1;
	t_ulong t2;

	t1 = m[7] + EP1(m[4]) + CH(m[4], m[5], m[6]) + g_sha512_k[i] + w[i];
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

void	sha512_fill_words(t_ulong *w)
{
	int		i;
	t_ulong	s0;
	t_ulong	s1;

	i = 16;
	while (i < 80)
	{
		s0 = ROTR(w[i - 15], 1) ^ ROTR(w[i - 15], 8) ^ (w[i - 15] >> 7);
		s1 = ROTR(w[i - 2], 19) ^ ROTR(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = s1 + w[i - 7] + s0 + w[i - 16];
		i++;
	}
}

void	sha512_process_block(t_uchar *block, t_ulong *old_buffer)
{
	int		i;
	t_ulong	w[80];
	t_ulong	new_buffer[8];

	sha512_str_to_long(w, block, 128);
	sha512_fill_words(w);
	ft_memcpy(new_buffer, old_buffer, 64);
	i = 0;
	while (i < 80)
	{
		sha512_round(new_buffer, w, i);
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

t_ulong	*sha512_init_buffer(void)
{
	t_ulong *buffer;

	buffer = malloc(8 * sizeof(t_ulong));
	buffer[0] = 0x6a09e667f3bcc908;
	buffer[1] = 0xbb67ae8584caa73b;
	buffer[2] = 0x3c6ef372fe94f82b;
	buffer[3] = 0xa54ff53a5f1d36f1;
	buffer[4] = 0x510e527fade682d1;
	buffer[5] = 0x9b05688c2b3e6c1f;
	buffer[6] = 0x1f83d9abfb41bd6b;
	buffer[7] = 0x5be0cd19137e2179;
	return (buffer);
}
