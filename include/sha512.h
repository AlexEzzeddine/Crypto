/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:23:43 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:48:37 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef struct			s_sha512_options
{
	int	printed;
	int	quiet;
	int	reverse;
}						t_sha512_options;

void					sha512_parse_args(char **args, int size);
t_ulong					*sha512_calculate_hash(t_uchar *input, int len);
void					sha512(char **args, int size);
t_uchar					*sha512_pad(t_uchar *old, int *old_len);
void					sha512_round(t_ulong *m, t_ulong *w, int i);
void					sha512_fill_words(t_ulong *w);
void					sha512_process_block(t_uchar *block,
							t_ulong *old_buffer);
t_ulong					*sha512_init_buffer(void);
int						sha512_read_all(int fd, t_uchar **output);
void					sha512_read_from_stdin(void);
void					sha512_read_from_stdin_and_echo(void);
void					sha512_read_from_string(char *str);
void					sha512_read_from_file(char *filename);
void					sha512_print_byte_in_hex(t_uchar c);
void					print_sha512_buffer(t_ulong *buffer);
void					sha512_print_string_hash(char *str, t_ulong *hash);
void					sha512_print_file_hash(char *filename, t_ulong *hash);
void					sha512_long_to_str(t_uchar *output,
							t_ulong *input, int len);
void					sha512_str_to_long(t_ulong *output,
							t_uchar *input, int len);
t_uint					sha512_rotate_left(t_uint x, int n);
t_uint					sha512_rotate_right(t_uint x, int n);
t_ulong					sha512_bswap_l(t_ulong x);

#endif
