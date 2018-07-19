/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 23:23:49 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 00:21:24 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern t_base64_options g_base64_options;

int		base64_open_input_fd(char *filename)
{
	int fd;

	if (!filename)
	{
		ft_putendl_fd("base64: option requires an argument -- i", 2);
		base64_usage();
		exit(1);
	}
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

int		base64_open_output_fd(char *filename)
{
	int fd;

	if (!filename)
	{
		ft_putendl_fd("base64: option requires an argument -- o", 2);
		base64_usage();
		exit(1);
	}
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

void	base64_usage(void)
{
	ft_putstr_fd("Usage: ft_ssl base64 [options]\n\n"
					"Options:\n"
					"\t-e: encode mode\n"
					"\t-d: decode mode\n"
					"\t-i file: input file\n"
					"\t-o file: output file\n", 2);
}

void	base64_invalid_option(char *option)
{
	ft_putstr_fd("ft_ssl base64: Error: \'", 2);
	ft_putstr_fd(option, 2);
	ft_putendl_fd("\' is an invalid option.", 2);
	ft_putchar_fd('\n', 2);
	base64_usage();
	exit(1);
}

void	base64_parse_args(char **args, int size)
{
	int i;

	i = 1;
	while (i < size)
	{
		if (!ft_strcmp(args[i], "-e"))
			g_base64_options.mode = ENCODE;
		else if (!ft_strcmp(args[i], "-d"))
			g_base64_options.mode = DECODE;
		else if (!ft_strcmp(args[i], "-i"))
			g_base64_options.fd_in = base64_open_input_fd(args[++i]);
		else if (!ft_strcmp(args[i], "-o"))
			g_base64_options.fd_out = base64_open_output_fd(args[++i]);
		else
			base64_invalid_option(args[i]);
		i++;
	}
}
