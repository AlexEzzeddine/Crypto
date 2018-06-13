/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:47:52 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 00:19:44 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

t_base64_options g_base64_options = {ENCODE, 0, 1};

t_uchar			*base64_encode(t_uchar *message, int *len)
{
	int		i;
	t_uchar	*cipher;

	i = 0;
	cipher = (t_uchar *)ft_strnew(4 * (*len / 3 + ((*len % 3) ? 1 : 0)));
	while (i < *len / 3)
	{
		pad_0(cipher + i * 4, message + i * 3);
		i++;
	}
	if (*len % 3 == 2)
		pad_1(cipher + i * 4, message + i * 3);
	else if (*len % 3 == 1)
		pad_2(cipher + i * 4, message + i * 3);
	if (*len)
	{
		cipher = (t_uchar *)ft_strfjoin((char *)cipher, "\n");
		*len = 4 * (*len / 3 + ((*len % 3) ? 1 : 0)) + 1;
	}
	cipher = add_newlines(cipher, len);
	return (cipher);
}

t_uchar			*base64_decode(t_uchar *cipher, int *len)
{
	int		i;
	t_uchar	*message;

	i = 0;
	*len = base64_check_padding(cipher, *len);
	message = (t_uchar *)ft_strnew(3 * (*len / 4) + (*len % 4 - 1));
	while (i < *len / 4)
	{
		message[3 * i + 0] = (base64_revchar(*(cipher + i * 4)) << 2)
		+ ((base64_revchar(*(cipher + i * 4 + 1)) & 0x30) >> 4);
		message[3 * i + 1] = (base64_revchar(*(cipher + i * 4 + 1)) << 4)
		+ (base64_revchar(*(cipher + i * 4 + 2)) >> 2);
		message[3 * i + 2] = (base64_revchar(*(cipher + i * 4 + 2)) << 6)
		+ base64_revchar(*(cipher + i * 4 + 3));
		i++;
	}
	if (*len % 4 > 1)
		message[3 * i + 0] = (base64_revchar(*(cipher + i * 4)) << 2)
		+ ((base64_revchar(*(cipher + i * 4 + 1)) & 0x30) >> 4);
	if (*len % 4 == 3)
		message[3 * i + 1] = (base64_revchar(*(cipher + i * 4 + 1)) << 4)
		+ (base64_revchar(*(cipher + i * 4 + 2)) >> 2);
	*len = 3 * (*len / 4) + (*len % 4 - 1);
	return (message);
}

static int		base64_read_all(int fd, t_uchar **output)
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

void			base64(char **args, int size)
{
	t_uchar	*input;
	t_uchar *output;
	int		len;

	base64_parse_args(args, size);
	len = base64_read_all(g_base64_options.fd_in, &input);
	close(g_base64_options.fd_in);
	if (g_base64_options.mode == ENCODE)
		output = base64_encode(input, &len);
	else
		output = base64_decode(input, &len);
	free(input);
	write(g_base64_options.fd_out, output, len);
	free(output);
	close(g_base64_options.fd_out);
}
