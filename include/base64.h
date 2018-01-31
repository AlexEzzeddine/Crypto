/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:49:17 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:39:23 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;

typedef enum			e_base64_mode
{
	ENCODE,
	DECODE
}						t_base64_mode;

typedef struct			s_base64_options
{
	t_base64_mode	mode;
	int				fd_in;
	int				fd_out;
}						t_base64_options;

t_uchar					*base64_encode(t_uchar *message, int *len);
t_uchar					*base64_decode(t_uchar *cipher, int *len);
void					base64(char **args, int size);

void					pad_0(t_uchar *cipher, t_uchar *message);
void					pad_1(t_uchar *cipher, t_uchar *message);
void					pad_2(t_uchar *cipher, t_uchar *message);

int						base64_open_input_fd(char *filename);
int						base64_open_output_fd(char *filename);
void					base64_usage();
void					base64_invalid_option(char *option);
void					base64_parse_args(char **args, int size);
int						base64_check_padding(t_uchar *cipher, int len);
t_uchar					base64_revchar(char ch);

#endif
