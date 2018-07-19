/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 00:25:07 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 03:16:18 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "base64.h"

t_des_options g_des_options = {NULL, Encrypt, 0, 0, 1, NULL, NULL};

void	des_ecb(t_uchar *message, t_uchar *cipher,
	t_ulong *key_schedule, int len)
{
	t_ulong	m;
	t_ulong	c;
	int		i;

	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		c = des_process_block(m, key_schedule, g_des_options.mode);
		long64_to_string(cipher + 8 * i, c);
		i++;
	}
}

void	des_cbc(t_uchar *message, t_uchar *cipher,
	t_ulong *key_schedule, int len)
{
	t_ulong	m;
	t_ulong	c;
	t_ulong iv;
	int		i;

	iv = convert_hex_to_bits(g_des_options.ivec);
	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		if (g_des_options.mode == Encrypt)
			m ^= iv;
		c = des_process_block(m, key_schedule, g_des_options.mode);
		if (g_des_options.mode == Decrypt)
			c ^= iv;
		iv = g_des_options.mode == Encrypt ? c : m;
		long64_to_string(cipher + 8 * i, c);
		i++;
	}
}

void	des_3(t_uchar *message, t_uchar *cipher,
	t_ulong **key_schedules, int len)
{
	t_ulong	m;
	t_ulong	c;
	t_ulong iv;
	int		i;

	iv = convert_hex_to_bits(g_des_options.ivec);
	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		if (g_des_options.mode == Encrypt)
			m ^= iv;
		c = des_process_block(m, key_schedules[0], g_des_options.mode);
		m = des_process_block(c, key_schedules[1], !g_des_options.mode);
		c = des_process_block(m, key_schedules[2], g_des_options.mode);
		if (g_des_options.mode == Encrypt)
			iv = c;
		else if (i > 0)
			iv = string_to_long64((t_uchar *)message + 8 * (i - 1));
		if (g_des_options.mode == Decrypt)
			c ^= iv;
		long64_to_string(cipher + 8 * i, c);
		i++;
	}
}

void	run_des(t_uchar *input, t_uchar *output, int len)
{
	if (!ft_strcmp(g_des_options.cipher, "des")
		|| !ft_strcmp(g_des_options.cipher, "des-ecb"))
		des_ecb(input, output, create_key_schedule(g_des_options.key), len);
	else if (!ft_strcmp(g_des_options.cipher, "des-cbc"))
		des_cbc(input, output, create_key_schedule(g_des_options.key), len);
	else if (!ft_strcmp(g_des_options.cipher, "des3"))
		des_3(input, output, create_3_key_schedule(g_des_options.key), len);
}

static void	des_encryption_padding(t_uchar **input, int *len)
{
	t_uchar *new_input;
	int diff;

	if (g_des_options.mode == Decrypt)
		return ;
	diff = 8 - *len % 8;
	new_input = (t_uchar *)ft_strrealloc((char *)(*input), diff);
	ft_memset(new_input + *len, diff, diff);
	*len += diff;
	free(*input);
	*input = new_input;
}

static int des_decryption_padding(t_uchar *input, int len)
{
	if (g_des_options.mode == Encrypt)
		return len;
	int diff = input[len - 1];
	return len - diff;
}

static void des_encryption_preprocessing()
{

}

static void des_decryption_preprocessing()
{

}

static void	des_preprocessing()
{
	if (g_des_options.mode == Encrypt)
		des_encryption_preprocessing();
	else
		des_decryption_preprocessing();
}

void	des(char **args, int size)
{
	t_uchar	*input;
	t_uchar	*output;
	int		len;

	des_parse_args(args, size);
	get_key();
	get_ivec();
	len = des_read_all(g_des_options.fd_in, &input);
	if (g_des_options.use_base64 && g_des_options.mode == Decrypt)
		input = base64_decode(input, &len);
	des_input_preprocessing(&input, &len);
	output = (t_uchar *)ft_strnew(len);
	run_des(input, output, len);
	len = des_decryption_padding(output, len);
	if (g_des_options.use_base64 && g_des_options.mode == Encrypt)
		output = (t_uchar *)base64_encode(output, &len);
	write(g_des_options.fd_out, output, len);
	close(g_des_options.fd_out);
}


void	des_pbkdf()
{
	t_uint key[2];
	t_uint iv[2];
	char *md5_input;
	t_uint *hash;
	md5_input = ft_strjoin(g_des_options.password, g_des_options.salt);
	hash = md5_calculate_hash(md5_input, ft_strlen(md5_input));
	ft_memcpy(key, hash, 8);
	ft_memcpy(iv, hash + 8, 8);
}