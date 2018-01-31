/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:40:07 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 00:17:24 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_ssl_command g_ssl_commands[COMMANDS_SIZE];

void	ssl_print_standard_commands(void)
{
	size_t i;
	size_t size;

	ft_putendl_fd("Standard commands:", 2);
	size = sizeof(g_ssl_commands) / sizeof(t_ssl_command);
	i = 0;
	while (i < size)
	{
		if (g_ssl_commands[i].type == STANDARD)
			ft_putendl_fd(g_ssl_commands[i].key, 2);
		i++;
	}
}

void	ssl_print_digest_commands(void)
{
	size_t i;
	size_t size;

	ft_putendl_fd("Message Digest commands:", 2);
	size = sizeof(g_ssl_commands) / sizeof(t_ssl_command);
	i = 0;
	while (i < size)
	{
		if (g_ssl_commands[i].type == DIGEST)
			ft_putendl_fd(g_ssl_commands[i].key, 2);
		i++;
	}
}

void	ssl_print_cipher_commands(void)
{
	size_t i;
	size_t size;

	ft_putendl_fd("Cipher commands:", 2);
	size = sizeof(g_ssl_commands) / sizeof(t_ssl_command);
	i = 0;
	while (i < size)
	{
		if (g_ssl_commands[i].type == CIPHER)
			ft_putendl_fd(g_ssl_commands[i].key, 2);
		i++;
	}
}

void	ssl_print_all_commands(void)
{
	ssl_print_standard_commands();
	ft_putchar_fd('\n', 2);
	ssl_print_digest_commands();
	ft_putchar_fd('\n', 2);
	ssl_print_cipher_commands();
}
