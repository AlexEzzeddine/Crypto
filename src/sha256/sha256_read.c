/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:47:21 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 02:12:14 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

extern t_sha256_options g_sha256_options;

int		sha256_read_all(int fd, t_uchar **output)
{
	char	*result;
	char	*old;
	char	*buf;
	int		n;
	int		len;

	buf = ft_strnew(10240);
	result = NULL;
	len = 0;
	while ((n = read(fd, buf, 10240)) > 0)
	{
		old = result;
		result = ft_strnew(len + n + 1);
		ft_memcpy(result, old, len);
		ft_memcpy(result + len, buf, n);
		len += n;
		free(old);
		ft_bzero(buf, 10240);
	}
	free(buf);
	*output = (t_uchar *)result;
	return (len);
}

void	sha256_read_from_stdin(void)
{
	int		len;
	t_uchar	*input;
	t_uint	*hash;

	g_sha256_options.printed = 1;
	len = sha256_read_all(0, &input);
	hash = sha256_calculate_hash(input, len);
	print_sha256_buffer(hash);
	ft_putchar('\n');
	free(hash);
}

void	sha256_read_from_stdin_and_echo(void)
{
	int		len;
	t_uchar	*input;
	t_uint	*hash;

	g_sha256_options.printed = 1;
	len = sha256_read_all(0, &input);
	write(1, input, len);
	hash = sha256_calculate_hash(input, len);
	print_sha256_buffer(hash);
	ft_putchar('\n');
	free(hash);
}

void	sha256_read_from_string(char *str)
{
	t_uint	*hash;

	g_sha256_options.printed = 1;
	hash = sha256_calculate_hash((t_uchar *)ft_strdup(str), ft_strlen(str));
	sha256_print_string_hash(str, hash);
	free(hash);
}

void	sha256_read_from_file(char *filename)
{
	int		len;
	t_uchar	*input;
	t_uint	*hash;
	int		fd;

	g_sha256_options.printed = 1;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr_fd("ft_ssl: sha256: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	len = sha256_read_all(fd, &input);
	hash = sha256_calculate_hash(input, len);
	sha256_print_file_hash(filename, hash);
	free(hash);
	close(fd);
}
