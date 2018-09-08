/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 10:06:23 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 11:12:00 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include "struct.h"
# include <fcntl.h>

# define BUFFSIZE	500000

# define RIGHTROTATE(x, n)	(((x >> n) | (x << (32 - n))))
# define RIGHTSHIFT(x, n)	(x >> n)
# define LEFTROTATE(x, n)	(((x << n) | (x >> (32 - n))))

/*
** FT_MD5
*/
# define F(x, y, z)	((x & y) | ((~x) & z))
# define G(x, y, z)	((x & z) | (y & (~z)))
# define H(x, y, z)	(x ^ y ^ z)
# define I(x, y, z)	(y ^ (x | (~z)))

/*
** FT_SHA256
*/
# define MAJ(x, y, z)	((x & y) ^ (x & z) ^ (y & z))
# define CH(x, y, z)	((x & y) ^ ((~x) & z))
# define E0(x)	(RIGHTROTATE(x, 2) ^ RIGHTROTATE(x, 13) ^ RIGHTROTATE(x, 22))
# define E1(x)	(RIGHTROTATE(x, 6) ^ RIGHTROTATE(x, 11) ^ RIGHTROTATE(x, 25))
# define S0(x)	(RIGHTROTATE(x, 7) ^ RIGHTROTATE(x, 18) ^ RIGHTSHIFT(x, 3))
# define S1(x)	(RIGHTROTATE(x, 17) ^ RIGHTROTATE(x, 19) ^ RIGHTSHIFT(x, 10))

/*
** FT_FUNCTIONS.c
*/
void		ft_message_sha256(char *str, t_message *m);
void		ft_message_md5(char *str, t_message *m);
char		*check_len_hexa(char *str);
void		ft_message_new(t_message *m, t_hash h, int max);
uint32_t	swap_int32(uint32_t x);

/*
** FT_HELPER.c
*/
char		*ft_fdtostr(int fd);
int			ft_checkfile(char *command, char *arg);
char		*str_toupper(char *str);
char		*str_tolower(char *str);

/*
** FT_CASES.c
*/
void		ft_printhash(char *str, char *command, t_message m, char flags);
char		*ft_command(char *command, t_message *m, int fd);
void		case_noarg(char *command, t_message m, char flags);
void		case_arg(char *command, char *arg, t_message m, char flags);
void		case_string(char *command, char *str, t_message m, char flags);
/*
** FT_SHA256.c
*/
void		ft_sha256(char *str, t_message *m);
void		ft_blocks_sha256(unsigned char	*padded, t_hash	*h);
void		ft_mainloop_sha256(t_reg r, t_hash *h, uint32_t *m);
uint32_t	*ft_register_sha256(t_reg *r, t_hash *h);
void		ft_rotation_sha256(t_reg r, t_hash *h, uint32_t *k, uint32_t *w);

/*
** FT_MD5.c
*/
void		ft_md5(char *str, t_message *m);
void		ft_blocks_md5(unsigned char *padded, t_hash *h);
void		ft_mainloop_md5(t_reg r, t_hash *h, uint32_t *m);
uint32_t	*ft_register_md5_1(t_reg *r, t_hash *h);
void		ft_rotation_md5(t_reg *r, uint32_t *m, uint32_t *k, uint32_t *s);

#endif
