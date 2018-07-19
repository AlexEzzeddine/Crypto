/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 02:01:36 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 02:17:59 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern t_des_options g_des_options;

void	get_ivec(void)
{
	if (!ft_strcmp(g_des_options.cipher, "des-cbc")
		|| !ft_strcmp(g_des_options.cipher, "des3"))
	{
		if (!(g_des_options.ivec))
		{
			g_des_options.ivec = ft_strnew(16);
			readpassphrase("enter initial vector: ",
				g_des_options.ivec, 17, RPP_ECHO_ON);
		}
		g_des_options.ivec = normalize_key(g_des_options.ivec, 16);
	}
}

void	get_key(void)
{
	int key_size;

	key_size = 16;
	if (!ft_strcmp(g_des_options.cipher, "des3"))
		key_size = 48;
	if (!(g_des_options.key))
	{
		g_des_options.key = ft_strnew(key_size);
		readpassphrase("enter des key in hex: ",
			g_des_options.key, key_size + 1, RPP_ECHO_ON);
	}
	g_des_options.key = normalize_key(g_des_options.key, key_size);
}

void	get_salt(void)
{
	int salt_size;

	salt_size = 16;
	if (!ft_strcmp(g_des_options.cipher, "des3"))
		salt_size = 48;
	if (!(g_des_options.salt))
	{
		g_des_options.salt = ft_strnew(salt_size);
		readpassphrase("enter des salt in hex: ",
			g_des_options.salt, salt_size + 1, RPP_ECHO_ON);
	}
	g_des_options.salt = normalize_key(g_des_options.salt, salt_size);
}

void	get_passsword(void)
{
	char passbuf[1024];
	if (!(g_des_options.password))
	{
		readpassphrase("enter password: ",
			passbuf, sizeof(passbuf), RPP_ECHO_ON);
		g_des_options.password = ft_strdup(passbuf);
	}
}

int des_salt(char **res)
{
	if (g_des_options.mode == Encrypt)
	{
		*res = ft_strnew(16);
		ft_memcpy(res, "Salted__", 8);
		ft_memcpy(res, g_des_options.salt, 8);
	}
	else
	{

	}
}

void		des_read_message()
{
	char	*result;
	char	*old;
	char	*buf;
	int		n;
	int		len;

	buf = ft_strnew(8);
	len = 0;
	while ((n = read(g_des_options.fd_in, buf, 8)) > 0)
	{
		old = result;
		result = ft_strnew(len + n + 1);
		ft_memcpy(result, old, len);
		ft_memcpy(result + len, buf, n);
		len += n;
		free(old);
		ft_bzero(buf, 8);
	}
	g_des_options.input = (t_uchar *)result;
	close(g_des_options.fd_in);
	g_des_options.input_len = len;
}

void des_read_salt()
{
	char magic[8];
	int n;

	n = 
}

void		des_read_cipher()
{
	char	*result;
	char	*old;
	char	*buf;
	int		n;
	int		len;

	buf = ft_strnew(8);
	des_read_salt();
	while ((n = read(g_des_options.fd_in, buf, 8)) > 0)
	{
		old = result;
		result = ft_strnew(len + n + 1);
		ft_memcpy(result, old, len);
		ft_memcpy(result + len, buf, n);
		len += n;
		free(old);
		ft_bzero(buf, 8);
	}
	g_des_options.input = (t_uchar *)result;
	close(g_des_options.fd_in);
	g_des_options.input_len = len;
}
