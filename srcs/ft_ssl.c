/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:25:24 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 12:37:03 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

void	ft_error(char *command, char option, int bool)
{
	if (!bool)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", command);
		ft_printf("Standard command: \n\n Message Digest commands:\nmd5");
		ft_printf("\nsha256\n\nCipher commands:\n");
	}
	else
	{
		ft_printf("%s: illegal option -- %c\n", command, option);
		ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", command);
	}
	exit(-1);
}

void	case_flags(char *command, t_message *m, char *argument, char *nextarg)
{
	m->i = 0;
	while (argument && argument[++m->i] && ft_strchr("pqrs", argument[m->i]))
	{
		if (argument[m->i] == 'r' && m->flags[0] != 0)
		{
			m->flags[0] = 4;
			m->flags[1] = 3;
		}
		else if (argument[m->i] == 'q')
		{
			m->flags[0] = 0;
			m->flags[1] = 0;
		}
		else if (argument[m->i] == 'p')
			case_noarg(command, *m, 5);
		else if (argument[m->i] == 's')
		{
			case_string(command, nextarg, *m, m->flags[0]);
			m->arg++;
		}
	}
	if (argument && argument[m->i] != '\0')
		ft_error(command, argument[m->i], 1);
	m->arg++;
}

void	init_variables(t_message *m)
{
	m->flags[0] = 2;
	m->flags[1] = 1;
	m->arg = 2;
}

int		main(int argc, char **argv)
{
	t_message m;

	init_variables(&m);
	if (argc <= 1)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (ft_strcmp(argv[1], "md5") == 0
		|| ft_strcmp(argv[1], "sha256") == 0)
	{
		if (argc < 3)
			case_noarg(argv[1], m, 0);
		else
		{
			while (argv[m.arg] && argv[m.arg][0] == '-')
				case_flags(argv[1], &m, argv[m.arg], argv[m.arg + 1]);
			if (!argv[m.arg] && ft_strchr("qr", argv[m.arg - 1][1]))
				case_noarg(argv[1], m, 0);
		}
		while (m.arg < argc)
			case_arg(argv[1], argv[m.arg++], m, m.flags[1]);
	}
	else
		ft_error(argv[1], 0, 0);
	return (0);
}
