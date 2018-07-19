/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 00:23:08 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:43:31 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readpassphrase.h>
# include "libft.h"

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef enum			e_encryption_mode
{
	Encrypt,
	Decrypt
}						t_encryption_mode;

typedef struct			s_des_options
{
	char				*cipher;
	t_encryption_mode	mode;
	int					use_base64;
	int					fd_in;
	int					fd_out;
	char				*key;
	char				*ivec;
	char				*salt;
	char				*password;
	t_uchar				*input;
	t_uchar				*output;
	int					input_len;
	int					output_len;
}						t_des_options;

void					des_ecb(t_uchar *message, t_uchar *cipher,
							t_ulong *key_schedule, int len);
void					des_cbc(t_uchar *message, t_uchar *cipher,
							t_ulong *key_schedule, int len);
void					des_3(t_uchar *message, t_uchar *cipher,
							t_ulong **key_schedules, int len);
void					run_des(t_uchar *input, t_uchar *output, int len);
void					des(char **args, int size);

t_ulong					string_to_long64(t_uchar *str);
void					long64_to_string(t_uchar *str, t_ulong n);
int						get_bit(t_ulong buf, t_ulong bit);
void					set_bit(t_ulong *buf, t_ulong bit);

t_ulong					permute(t_ulong old_block,
							const int *permutation_map, int size);
t_ulong					magic(t_ulong m, t_ulong k);
t_ulong					des_round(t_ulong m, t_ulong k);
t_ulong					des_process_block
						(t_ulong m, t_ulong *keys, t_encryption_mode mode);
t_ulong					char_to_hex_digit(char c);
t_ulong					convert_hex_to_bits(char *key);

char					*normalize_key(char *old_key, int key_size);
t_ulong					rotate_sub_key(t_ulong key, int shift);
t_ulong					*create_key_schedule(char *key);
t_ulong					**create_3_key_schedule(char *key_192);

void					des_parse_args(char **args, int size);
void					get_ivec(void);
void					get_key(void);
int						des_read_all(int fd, t_uchar **output);

#endif
