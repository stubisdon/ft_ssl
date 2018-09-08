/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 09:19:04 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 12:27:40 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

void		ft_sha256(char *str, t_message *m)
{
	int			size;
	t_hash		h;

	h.h[0] = 0x6a09e667;
	h.h[1] = 0xbb67ae85;
	h.h[2] = 0x3c6ef372;
	h.h[3] = 0xa54ff53a;
	h.h[4] = 0x510e527f;
	h.h[5] = 0x9b05688c;
	h.h[6] = 0x1f83d9ab;
	h.h[7] = 0x5be0cd19;
	ft_message_sha256(str, m);
	size = 0;
	while (size < m->buffsize)
	{
		ft_blocks_sha256(&m->padded[size], &h);
		size += 64;
	}
	free(m->padded);
	ft_message_new(m, h, 8);
}

void		ft_blocks_sha256(unsigned char *padded, t_hash *h)
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
		m[i] = swap_int32(m[i]);
		size += 4;
	}
	ft_mainloop_sha256(r, h, m);
}

void		ft_mainloop_sha256(t_reg r, t_hash *h, uint32_t *m)
{
	int			i;
	uint32_t	w[64];
	uint32_t	*k;

	k = ft_register_sha256(&r, h);
	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			w[i] = m[i];
		else
			w[i] = S1(w[i - 2]) + w[i - 7] + S0(w[i - 15]) + w[i - 16];
	}
	ft_rotation_sha256(r, h, k, w);
}

uint32_t	*ft_register_sha256(t_reg *r, t_hash *h)
{
	static uint32_t k[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
		0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
		0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
		0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
		0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
		0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	r->a = h->h[0];
	r->b = h->h[1];
	r->c = h->h[2];
	r->d = h->h[3];
	r->e = h->h[4];
	r->f = h->h[5];
	r->g = h->h[6];
	r->h = h->h[7];
	return (k);
}

void		ft_rotation_sha256(t_reg r, t_hash *h, uint32_t *k, uint32_t *w)
{
	int	i;

	i = -1;
	while (++i < 64)
	{
		r.t1 = r.h + E1(r.e) + CH(r.e, r.f, r.g) + k[i] + w[i];
		r.t2 = E0(r.a) + MAJ(r.a, r.b, r.c);
		r.h = r.g;
		r.g = r.f;
		r.f = r.e;
		r.e = r.d + r.t1;
		r.d = r.c;
		r.c = r.b;
		r.b = r.a;
		r.a = r.t1 + r.t2;
	}
	h->h[0] = h->h[0] + r.a;
	h->h[1] = h->h[1] + r.b;
	h->h[2] = h->h[2] + r.c;
	h->h[3] = h->h[3] + r.d;
	h->h[4] = h->h[4] + r.e;
	h->h[5] = h->h[5] + r.f;
	h->h[6] = h->h[6] + r.g;
	h->h[7] = h->h[7] + r.h;
}
