/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:08:01 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 03:18:36 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern t_des_options g_des_options;

int		des_open_input_fd(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Unable to open \'", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\': ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return (fd);
}

int		des_open_output_fd(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("Unable to open \'", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\': ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return (fd);
}

void	des_usage(void)
{
	ft_putstr_fd("Usage: ft_ssl ", 2);
	ft_putstr_fd(g_des_options.cipher, 2);
	ft_putstr_fd(": [options]\n\n"
					"Options:\n"
					"\t-e: encryption mode\n"
					"\t-d: decryption mode\n"
					"\t-a: encode input to base64 before encryption"
					" (in encryption mode)\n"
					"\t\tor decode from base64 after decryption"
					" (in decryption mode)\n"
					"\t-k: key in hex. Example: 0123FF42dd1f0fcc\n"
					"\t-v (only in cbc mode): initialization vector in hex."
					"Example: 0123FF42dd1f0fcc\n"
					"\t-i file: input file\n"
					"\t-o file: output file\n", 2);
}

void	des_invalid_option(char *option)
{
	ft_putstr_fd("ft_ssl ", 2);
	ft_putstr_fd(g_des_options.cipher, 2);
	ft_putstr_fd(": Error: \'", 2);
	ft_putstr_fd(option, 2);
	ft_putendl_fd("\' is an invalid option.", 2);
	ft_putchar_fd('\n', 2);
	des_usage();
	exit(1);
}

void	des_parse_args(char **args, int size)
{
	int i;

	g_des_options.cipher = args[0];
	i = 0;
	while (++i < size)
	{
		if (!ft_strcmp(args[i], "-e"))
			g_des_options.mode = Encrypt;
		else if (!ft_strcmp(args[i], "-d"))
			g_des_options.mode = Decrypt;
		else if (!ft_strcmp(args[i], "-a"))
			g_des_options.use_base64 = 1;
		else if (!ft_strcmp(args[i], "-i"))
			g_des_options.fd_in = des_open_input_fd(args[++i]);
		else if (!ft_strcmp(args[i], "-o"))
			g_des_options.fd_out = des_open_output_fd(args[++i]);
		else if (!ft_strcmp(args[i], "-k"))
			g_des_options.key = args[++i];
		else if (!ft_strcmp(args[i], "-v") &&
			(!ft_strcmp(g_des_options.cipher, "des3")
			|| !ft_strcmp(g_des_options.cipher, "des-cbc")))
			g_des_options.ivec = args[++i];
		else
			des_invalid_option(args[i]);
	}
}
