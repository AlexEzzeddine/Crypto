/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:01:38 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/29 20:01:54 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

t_uchar g_charset[] =
{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

void	pad_0(t_uchar *cipher, t_uchar *message)
{
	cipher[0] = g_charset[*message >> 2];
	cipher[1] = g_charset[((*message & 0x03) << 4) + (*(message + 1) >> 4)];
	cipher[2] = g_charset[((*(message + 1) & 0x0F) << 2)
	+ (*(message + 2) >> 6)];
	cipher[3] = g_charset[*(message + 2) & 0x3F];
}

void	pad_1(t_uchar *cipher, t_uchar *message)
{
	cipher[0] = g_charset[*message >> 2];
	cipher[1] = g_charset[((*message & 0x03) << 4) + (*(message + 1) >> 4)];
	cipher[2] = g_charset[(*(message + 1) & 0x0F) << 2];
	cipher[3] = '=';
}

void	pad_2(t_uchar *cipher, t_uchar *message)
{
	cipher[0] = g_charset[*message >> 2];
	cipher[1] = g_charset[(*message & 0x03) << 4];
	cipher[2] = '=';
	cipher[3] = '=';
}
