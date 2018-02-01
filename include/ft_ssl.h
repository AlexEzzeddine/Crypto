/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 03:07:10 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 18:12:40 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef char			*t_ssl_command_key;

typedef void			(*t_ssl_command_func)(char **, int);

typedef enum			e_ssl_command_type
{
	STANDARD,
	DIGEST,
	CIPHER
}						t_ssl_command_type;

typedef struct			s_ssl_command
{
	t_ssl_command_key	key;
	t_ssl_command_func	func;
	t_ssl_command_type	type;
}						t_ssl_command;

# define COMMANDS_SIZE 9

void					ssl_print_standard_commands(void);
void					ssl_print_digest_commands(void);
void					ssl_print_cipher_commands(void);
void					ssl_print_all_commands(void);
void					ssl_usage(void);
void					ssl_help(char **args, int len);
void					ssl_invalid_command(char *command);
t_ssl_command_func		ssl_get_command(char *arg);

#endif
