/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:46:19 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 00:31:16 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

t_sha256_options g_sha256_options = {0, 0, 0};

void	sha256_parse_string(char *str)
{
	g_sha256_options.printed = 1;
	if (str)
		sha256_read_from_string(str);
	else
		ft_putendl_fd("sha256: option requires an argument -- s", 2);
}

void	sha256_parse_args(char **args, int size)
{
	int i;

	i = 1;
	while (i < size)
	{
		if (!ft_strcmp(args[i], "-p"))
			sha256_read_from_stdin_and_echo();
		else if (!ft_strcmp(args[i], "-q"))
			g_sha256_options.quiet = 1;
		else if (!ft_strcmp(args[i], "-r"))
			g_sha256_options.reverse = 1;
		else if (!ft_strcmp(args[i], "-s"))
			sha256_parse_string(args[++i]);
		else
			while (i < size)
				sha256_read_from_file(args[i++]);
		i++;
	}
}

t_uint	*sha256_calculate_hash(t_uchar *input, int len)
{
	int		i;
	t_uint	*buffer;

	buffer = sha256_init_buffer();
	input = sha256_pad(input, &len);
	i = 0;
	while (i < len / 64)
	{
		sha256_process_block(input + i * 64, buffer);
		i++;
	}
	free(input);
	return (buffer);
}

void	sha256(char **args, int size)
{
	sha256_parse_args(args, size);
	if (!g_sha256_options.printed)
		sha256_read_from_stdin();
}
