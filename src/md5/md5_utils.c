/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 06:11:52 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 19:11:23 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	md5_int_to_str(t_uchar *output, t_uint *input, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (t_uchar)(input[i] & 0xff);
		output[j + 1] = (t_uchar)((input[i] >> 8) & 0xff);
		output[j + 2] = (t_uchar)((input[i] >> 16) & 0xff);
		output[j + 3] = (t_uchar)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	md5_str_to_int(t_uint *output, t_uchar *input, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((t_uint)input[j])
					| (((t_uint)input[j + 1]) << 8)
					| (((t_uint)input[j + 2]) << 16)
					| (((t_uint)input[j + 3]) << 24);
		i++;
		j += 4;
	}
}

t_uint	md5_rotate_left(t_uint x, int n)
{
	return (x << n) | (x >> (32 - n));
}
