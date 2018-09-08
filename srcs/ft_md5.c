/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:36:01 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 12:28:46 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

void		ft_md5(char *str, t_message *m)
{
	int			size;
	t_hash		h;

	h.h[0] = 0x67452301;
	h.h[1] = 0xefcdab89;
	h.h[2] = 0x98badcfe;
	h.h[3] = 0x10325476;
	ft_message_md5(str, m);
	size = 0;
	while (size < m->buffsize)
	{
		ft_blocks_md5(&m->padded[size], &h);
		size += 64;
	}
	free(m->padded);
	h.h[0] = swap_int32(h.h[0]);
	h.h[1] = swap_int32(h.h[1]);
	h.h[2] = swap_int32(h.h[2]);
	h.h[3] = swap_int32(h.h[3]);
	ft_message_new(m, h, 4);
}

void		ft_blocks_md5(unsigned char *padded, t_hash *h)
{
	int			i;
	int			size;
	uint32_t	m[16];
	t_reg		r;

	i = -1;
	size = 0;
	while (++i < 16)
	{
		ft_memcpy(&m[i], (padded + size), 4);
		size += 4;
	}
	ft_mainloop_md5(r, h, m);
}

void		ft_rotation_md5(t_reg *r, uint32_t *m, uint32_t *k, uint32_t *s)
{
	if (r->t1 < 16)
	{
		r->f = F(r->b, r->c, r->d);
		r->g = r->t1;
	}
	else if (r->t1 < 32)
	{
		r->f = G(r->b, r->c, r->d);
		r->g = ((5 * r->t1) + 1) % 16;
	}
	else if (r->t1 < 48)
	{
		r->f = H(r->b, r->c, r->d);
		r->g = ((3 * r->t1) + 5) % 16;
	}
	else if (r->t1 < 64)
	{
		r->f = I(r->b, r->c, r->d);
		r->g = (7 * r->t1) % 16;
	}
	r->e = r->d;
	r->d = r->c;
	r->c = r->b;
	r->b = r->b + LEFTROTATE((r->f + r->a + k[r->t1] + m[r->g]), s[r->t1]);
	r->a = r->e;
}

void		ft_mainloop_md5(t_reg r, t_hash *h, uint32_t *m)
{
	uint32_t		*k;
	static uint32_t	s[64] = {
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	k = ft_register_md5_1(&r, h);
	r.t1 = -1;
	while (++r.t1 < 64)
		ft_rotation_md5(&r, m, k, s);
	h->h[0] = h->h[0] + r.a;
	h->h[1] = h->h[1] + r.b;
	h->h[2] = h->h[2] + r.c;
	h->h[3] = h->h[3] + r.d;
}

uint32_t	*ft_register_md5_1(t_reg *r, t_hash *h)
{
	static uint32_t	k[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
		0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
		0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
		0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
		0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
		0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	r->a = h->h[0];
	r->b = h->h[1];
	r->c = h->h[2];
	r->d = h->h[3];
	return (k);
}
