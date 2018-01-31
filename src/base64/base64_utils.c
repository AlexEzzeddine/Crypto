/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 00:09:53 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/30 00:10:32 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

int		base64_check_padding(t_uchar *cipher, int len)
{
	if (len && cipher[len - 1] == '=')
		len--;
	if (len && cipher[len - 1] == '=')
		len--;
	return (len);
}

t_uchar	base64_revchar(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch -= 'A';
	else if (ch >= 'a' && ch <= 'z')
		ch = ch - 'a' + 26;
	else if (ch >= '0' && ch <= '9')
		ch = ch - '0' + 52;
	else if (ch == '+')
		ch = 62;
	else if (ch == '/')
		ch = 63;
	else
		ch = 0;
	return (ch);
}
