/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 03:19:17 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:45:50 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef struct			s_md5_options
{
	int	printed;
	int	quiet;
	int	reverse;
}						t_md5_options;

typedef struct			s_md5
{
	t_uint	a;
	t_uint	b;
	t_uint	c;
	t_uint	d;
	int		index;
	t_uint	shift;
	t_uint	sin;
}						t_md5;

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

void					md5(char **args, int size);
void					md5_parse_args(char **args, int size);
int						md5_read_all(int fd, t_uchar **output);
void					md5_print_byte_in_hex(t_uchar c);
void					print_md5_buffer(t_uint *buffer);
void					md5_read_from_stdin(void);
void					md5_read_from_stdin_and_echo(void);
void					md5_print_string_hash(char *str, t_uint *hash);
void					md5_print_file_hash(char *filename, t_uint *hash);
void					md5_read_from_string(char *str);
void					md5_read_from_file(char *filename);
t_uchar					*md5_pad(t_uchar *old, int *old_len);
void					md5_int_to_str(t_uchar *output, t_uint *input, int len);
void					md5_str_to_int(t_uint *output, t_uchar *input, int len);
unsigned int			md5_rotate_left(unsigned int x, int n);
void					md5_round(t_uint *buffer, t_uint *x, int i);
void					md5_process_block(t_uchar *block, t_uint *old_buffer);
t_uint					*md5_calculate_hash(t_uchar *input, int len);
t_uint					*md5_init_buffer(void);

#endif
