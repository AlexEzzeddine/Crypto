/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_ops.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 02:19:14 by aezzeddi          #+#    #+#             */
/*   Updated: 2018/01/31 03:47:18 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_OPS_H
# define SHA256_OPS_H

# define ROTL(a,b) (((a) << (b)) | ((a) >> (32-(b))))
# define ROTR(a,b) (((a) >> (b)) | ((a) << (32-(b))))
# define EP0(x) (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22))
# define EP1(x) (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25))
# define MA(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))

#endif
