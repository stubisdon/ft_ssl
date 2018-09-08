/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:12:55 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 11:13:19 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_reg
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		t1;
	uint32_t		t2;
}					t_reg;

typedef struct		s_hash
{
	uint32_t		h[8];
}					t_hash;

typedef struct		s_message
{
	size_t			buffsize;
	unsigned char	*padded;
	char			*message;
	int				flags[2];
	int				arg;
	int				i;
}					t_message;

typedef void		(*t_fct) (char *, t_message *);

typedef struct		s_dispatch
{
	int				command;
	t_fct			fct;
}					t_dispatch;

extern t_dispatch	g_command[];

#endif
