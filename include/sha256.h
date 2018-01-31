/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:23:43 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:47:02 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef struct			s_sha256_options
{
	int	printed;
	int	quiet;
	int	reverse;
}						t_sha256_options;

void					sha256_parse_args(char **args, int size);
void					sha256(char **args, int size);
t_uchar					*sha256_pad(t_uchar *old, int *old_len);
void					sha256_round(t_uint *m, t_uint *w, int i);
void					sha256_fill_words(t_uint *w);
void					sha256_process_block(t_uchar *block,
							t_uint *old_buffer);
t_uint					*sha256_init_buffer(void);
t_uint					*sha256_calculate_hash(t_uchar *input, int len);
void					sha256_print_byte_in_hex(t_uchar c);
void					print_sha256_buffer(t_uint *buffer);
void					sha256_print_string_hash(char *str, t_uint *hash);
void					sha256_print_file_hash(char *filename, t_uint *hash);
int						sha256_read_all(int fd, t_uchar **output);
void					sha256_read_from_stdin(void);
void					sha256_read_from_stdin_and_echo(void);
void					sha256_read_from_string(char *str);
void					sha256_read_from_file(char *filename);

void					sha256_int_to_str(t_uchar *output,
							t_uint *input, int len);
void					sha256_str_to_int(t_uint *output,
							t_uchar *input, int len);
t_uint					sha256_rotate_left(t_uint x, int n);
t_uint					sha256_rotate_right(t_uint x, int n);
t_ulong					sha256_bswap_l(t_ulong n);

#endif
