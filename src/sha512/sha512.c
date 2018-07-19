/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:46:19 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 02:07:28 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

t_sha512_options g_sha512_options = {0, 0, 0};

void	sha512_parse_string(char *str)
{
	g_sha512_options.printed = 1;
	if (str)
		sha512_read_from_string(str);
	else
		ft_putendl_fd("sha512: option requires an argument -- s", 2);
}

void	sha512_parse_args(char **args, int size)
{
	int i;

	i = 1;
	while (i < size)
	{
		if (!ft_strcmp(args[i], "-p"))
			sha512_read_from_stdin_and_echo();
		else if (!ft_strcmp(args[i], "-q"))
			g_sha512_options.quiet = 1;
		else if (!ft_strcmp(args[i], "-r"))
			g_sha512_options.reverse = 1;
		else if (!ft_strcmp(args[i], "-s"))
			sha512_parse_string(args[++i]);
		else
			while (i < size)
				sha512_read_from_file(args[i++]);
		i++;
	}
}

t_ulong	*sha512_calculate_hash(t_uchar *input, int len)
{
	int		i;
	t_ulong	*buffer;

	buffer = sha512_init_buffer();
	input = sha512_pad(input, &len);
	i = 0;
	while (i < len / 128)
	{
		sha512_process_block(input + i * 128, buffer);
		i++;
	}
	free(input);
	return (buffer);
}

void	sha512(char **args, int size)
{
	sha512_parse_args(args, size);
	if (!g_sha512_options.printed)
		sha512_read_from_stdin();
}
