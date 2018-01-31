/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:47:05 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 20:26:33 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

extern t_sha256_options g_sha256_options;

void	sha256_print_byte_in_hex(t_uchar c)
{
	static char hex[16] = "0123456789abcdef";

	ft_putchar(hex[c >> 4]);
	ft_putchar(hex[c & 0x0F]);
}

void	print_sha256_buffer(t_uint *buffer)
{
	int i;

	i = 0;
	while (i < 8)
	{
		sha256_print_byte_in_hex((t_uchar)(buffer[i] >> 24));
		sha256_print_byte_in_hex((t_uchar)(buffer[i] >> 16));
		sha256_print_byte_in_hex((t_uchar)(buffer[i] >> 8));
		sha256_print_byte_in_hex((t_uchar)buffer[i]);
		i++;
	}
}

void	sha256_print_string_hash(char *str, t_uint *hash)
{
	if (g_sha256_options.quiet)
		print_sha256_buffer(hash);
	else if (g_sha256_options.reverse)
	{
		print_sha256_buffer(hash);
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putstr("\"");
	}
	else
	{
		ft_putstr("sha256 (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
		print_sha256_buffer(hash);
	}
	ft_putchar('\n');
}

void	sha256_print_file_hash(char *filename, t_uint *hash)
{
	if (g_sha256_options.quiet)
		print_sha256_buffer(hash);
	else if (g_sha256_options.reverse)
	{
		print_sha256_buffer(hash);
		ft_putstr(" ");
		ft_putstr(filename);
	}
	else
	{
		ft_putstr("sha256 (");
		ft_putstr(filename);
		ft_putstr(") = ");
		print_sha256_buffer(hash);
	}
	ft_putchar('\n');
}
