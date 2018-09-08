/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:14:02 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 11:51:02 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

void		ft_message_sha256(char *str, t_message *m)
{
	int			i;
	uint64_t	size;

	size = ft_strlen(str);
	m->buffsize = 64;
	while ((m->buffsize - 8) <= size)
		m->buffsize += 64;
	m->padded = (unsigned char *)ft_strnew(m->buffsize);
	i = -1;
	while (str[++i])
		m->padded[i] = str[i];
	m->padded[i] = 0x00000080;
	i = 4;
	size = swap_int32(size * 8);
	ft_memcpy(&m->padded[m->buffsize - i], &size, i);
}

void		ft_message_md5(char *str, t_message *m)
{
	int			i;
	uint64_t	size;

	size = ft_strlen(str);
	m->buffsize = 64;
	while ((m->buffsize - 8) <= size)
		m->buffsize += 64;
	m->padded = (unsigned char *)ft_strnew(m->buffsize);
	i = -1;
	while (str[++i])
		m->padded[i] = str[i];
	m->padded[i] = 0x00000080;
	size = size * 8;
	ft_memcpy(&m->padded[m->buffsize - 8], &size, 8);
}

void		ft_message_new(t_message *m, t_hash h, int max)
{
	int		i;
	char	*tmp;
	char	*hash;
	char	*message;

	message = ft_strnew(64);
	i = -1;
	while (++i < max)
	{
		hash = ft_itoa_base(h.h[i], 16);
		tmp = ft_strjoin(message, hash);
		free(message);
		message = tmp;
	}
	m->message = message;
}

uint32_t	swap_int32(uint32_t x)
{
	x = ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) |
			((x >> 8) & 0xff00) | ((x << 24) & 0xff000000);
	return (x);
}
