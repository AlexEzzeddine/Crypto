/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 02:58:34 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 18:40:14 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include "des.h"
#include "md5.h"
#include "sha256.h"
#include "sha512.h"

t_ssl_command g_ssl_commands[] =
{
	{"base64", &base64, CIPHER},
	{"des", &des, CIPHER},
	{"des-ecb", &des, CIPHER},
	{"des-cbc", &des, CIPHER},
	{"des3", &des, CIPHER},
	{"md5", &md5, DIGEST},
	{"sha256", &sha256, DIGEST},
	{"sha512", &sha512, DIGEST},
	{"help", &ssl_help, STANDARD},
};

void				ssl_usage(void)
{
	ft_putendl_fd("usage: ft_ssl command [command opts] [command args]", 2);
}

void				ssl_help(char **args, int len)
{
	(void)args;
	(void)len;
	ssl_usage();
	ft_putchar_fd('\n', 2);
	ssl_print_all_commands();
}

void				ssl_invalid_command(char *command)
{
	ft_putstr_fd("ft_ssl: Error: \'", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("\' is an invalid command.", 2);
	ft_putchar_fd('\n', 2);
	ssl_print_all_commands();
}

t_ssl_command_func	ssl_get_command(char *arg)
{
	size_t i;
	size_t size;

	i = 0;
	size = sizeof(g_ssl_commands) / sizeof(t_ssl_command);
	while (i < size)
	{
		if (!ft_strcmp(arg, g_ssl_commands[i].key))
			return (g_ssl_commands[i].func);
		i++;
	}
	return (NULL);
}

int					main(int argc, char **argv)
{
	t_ssl_command_func ssl_command;

	if (argc < 2)
	{
		ssl_usage();
		return (1);
	}
	if (!(ssl_command = ssl_get_command(argv[1])))
	{
		ssl_invalid_command(argv[1]);
		return (1);
	}
	(*ssl_command)(argv + 1, argc - 1);
	return (0);
}
