/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_ops.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 02:17:29 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:47:34 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_OPS_H
# define SHA512_OPS_H

# define ROTL(a,b) (((a) << (b)) | ((a) >> (64-(b))))
# define ROTR(a,b) (((a) >> (b)) | ((a) << (64-(b))))
# define EP0(x) (ROTR(x,28) ^ ROTR(x,34) ^ ROTR(x,39))
# define EP1(x) (ROTR(x,14) ^ ROTR(x,18) ^ ROTR(x,41))
# define MA(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))

#endif
