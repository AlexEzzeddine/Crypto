/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:47:05 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 02:23:06 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

extern t_sha512_options g_sha512_options;

void	sha512_print_byte_in_hex(t_uchar c)
{
	static char hex[16] = "0123456789abcdef";

	ft_putchar(hex[c >> 4]);
	ft_putchar(hex[c & 0x0F]);
}

void	print_sha512_buffer(t_ulong *buffer)
{
	int i;

	i = 0;
	while (i < 8)
	{
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 56));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 48));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 40));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 32));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 24));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 16));
		sha512_print_byte_in_hex((t_uchar)(buffer[i] >> 8));
		sha512_print_byte_in_hex((t_uchar)buffer[i]);
		i++;
	}
}

void	sha512_print_string_hash(char *str, t_ulong *hash)
{
	if (g_sha512_options.quiet)
		print_sha512_buffer(hash);
	else if (g_sha512_options.reverse)
	{
		print_sha512_buffer(hash);
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putstr("\"");
	}
	else
	{
		ft_putstr("sha512 (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
		print_sha512_buffer(hash);
	}
	ft_putchar('\n');
}

void	sha512_print_file_hash(char *filename, t_ulong *hash)
{
	if (g_sha512_options.quiet)
		print_sha512_buffer(hash);
	else if (g_sha512_options.reverse)
	{
		print_sha512_buffer(hash);
		ft_putstr(" ");
		ft_putstr(filename);
	}
	else
	{
		ft_putstr("sha512 (");
		ft_putstr(filename);
		ft_putstr(") = ");
		print_sha512_buffer(hash);
	}
	ft_putchar('\n');
}
