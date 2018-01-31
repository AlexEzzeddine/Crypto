/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:06:01 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 19:12:06 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

extern t_md5_options g_md5_options;

void	md5_print_byte_in_hex(t_uchar c)
{
	static char hex[16] = "0123456789abcdef";

	ft_putchar(hex[c >> 4]);
	ft_putchar(hex[c & 0x0F]);
}

void	print_md5_buffer(t_uint *buffer)
{
	int i;

	i = 0;
	while (i < 4)
	{
		md5_print_byte_in_hex((t_uchar)buffer[i]);
		md5_print_byte_in_hex((t_uchar)(buffer[i] >> 8));
		md5_print_byte_in_hex((t_uchar)(buffer[i] >> 16));
		md5_print_byte_in_hex((t_uchar)(buffer[i] >> 24));
		i++;
	}
}

void	md5_print_string_hash(char *str, t_uint *hash)
{
	if (g_md5_options.quiet)
		print_md5_buffer(hash);
	else if (g_md5_options.reverse)
	{
		print_md5_buffer(hash);
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putstr("\"");
	}
	else
	{
		ft_putstr("MD5 (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
		print_md5_buffer(hash);
	}
	ft_putchar('\n');
}

void	md5_print_file_hash(char *filename, t_uint *hash)
{
	if (g_md5_options.quiet)
		print_md5_buffer(hash);
	else if (g_md5_options.reverse)
	{
		print_md5_buffer(hash);
		ft_putstr(" ");
		ft_putstr(filename);
	}
	else
	{
		ft_putstr("MD5 (");
		ft_putstr(filename);
		ft_putstr(") = ");
		print_md5_buffer(hash);
	}
	ft_putchar('\n');
}
