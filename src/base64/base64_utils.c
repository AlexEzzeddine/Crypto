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

t_uchar	*add_newlines(t_uchar *cipher, int *len)
{
	t_uchar	*newcipher;
	int		i;
	int		j;

	if (!(*len / 64))
		return (cipher);
	newcipher = malloc(*len + *len / 64);
	i = 0;
	j = 0;
	while (j < *len)
	{
		newcipher[i] = cipher[j];
		i++;
		j++;
		if (j && j % 64 == 0)
		{
			newcipher[i] = '\n';
			i++;
		}
	}
	*len = i;
	free(cipher);
	return (newcipher);
}

int		remove_whitespaces(t_uchar *msg, int len)
{
	int i;
	int j;

	if (!len)
		return (0);
	i = 0;
	j = 0;
	while (j < len)
	{
		while (msg[j] == ' ' || msg[j] == '\n')
			j++;
		msg[i] = msg[j];
		i++;
		j++;
	}
	msg[i] = '\0';
	return (i);
}

int		base64_check_padding(t_uchar *cipher, int len)
{
	len = remove_whitespaces(cipher, len);
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
