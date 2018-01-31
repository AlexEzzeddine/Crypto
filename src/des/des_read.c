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

int		des_read_all(int fd, t_uchar **output)
{
	char	*result;
	char	*old;
	char	*buf;
	int		n;
	int		len;

	buf = ft_strnew(8);
	result = NULL;
	len = 0;
	while ((n = read(fd, buf, 8)) > 0)
	{
		old = result;
		result = ft_strnew(len + n + 1);
		ft_memcpy(result, old, len);
		ft_memcpy(result + len, buf, n);
		len += n;
		free(old);
		ft_bzero(buf, 8);
	}
	*output = (t_uchar *)result;
	return (len);
}
