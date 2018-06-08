/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 03:20:15 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 06:07:56 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_md5_options g_md5_options = {0, 0, 0};

static void md5_parse_string(char *str)
{
	g_md5_options.printed = 1;
	if (str)
		md5_read_from_string(str);
	else
		ft_putendl_fd("md5: option requires an argument -- s", 2);
}

void	md5_parse_args(char **args, int size)
{
	int i;

	i = 1;
	while (i < size)
	{
		if (!ft_strcmp(args[i], "-p"))
			md5_read_from_stdin_and_echo();
		else if (!ft_strcmp(args[i], "-q"))
			g_md5_options.quiet = 1;
		else if (!ft_strcmp(args[i], "-r"))
			g_md5_options.reverse = 1;
		else if (!ft_strcmp(args[i], "-s"))
			md5_parse_string(args[++i]);
		else
			while (i < size)
				md5_read_from_file(args[i++]);
		i++;
	}
}

void	md5(char **args, int size)
{
	md5_parse_args(args, size);
	if (!g_md5_options.printed)
		md5_read_from_stdin();
}
