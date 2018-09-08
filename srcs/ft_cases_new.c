/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cases_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:46:15 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 11:38:16 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

#define NUMBERCOMMAND 2

t_dispatch g_command[] = {
	{0, &ft_md5},
	{1, &ft_sha256}
};

void	ft_printhash(char *str, char *command, t_message m, char flags)
{
	if (flags == 0)
		ft_printf("%s\n", m.message);
	else if (flags == 1)
		ft_printf("%s (%s) = %s\n", str_toupper(command), str, m.message);
	else if (flags == 2)
		ft_printf("%s (\"%s\") = %s\n", str_toupper(command), str, m.message);
	else if (flags == 3)
		ft_printf("%s %s\n", m.message, str);
	else if (flags == 4)
		ft_printf("%s \"%s\"\n", m.message, str);
	else if (flags == 5)
		ft_printf("%s%s\n", str, m.message);
	str_tolower(command);
}

char	*ft_command(char *command, t_message *m, int fd)
{
	int		i;
	int		choice;
	char	*str;

	choice = 0;
	str = ft_fdtostr(fd);
	if (ft_strcmp(command, "sha256") == 0)
		choice = 1;
	i = -1;
	while (++i < NUMBERCOMMAND)
	{
		if (g_command[i].command == choice)
			g_command[i].fct(str, m);
	}
	return (str);
}

void	case_noarg(char *command, t_message m, char flags)
{
	char	*str;

	str = ft_command(command, &m, 0);
	ft_printhash(str, command, m, flags);
}

void	case_arg(char *command, char *arg, t_message m, char flags)
{
	int		fd;
	char	*str;

	if ((fd = ft_checkfile(command, arg)) != -1)
	{
		str = ft_command(command, &m, fd);
		ft_printhash(arg, command, m, flags);
	}
}

void	case_string(char *command, char *str, t_message m, char flags)
{
	if (str == NULL)
	{
		ft_printf("md5: option requires an argument -- s\n");
		ft_printf("usage: %s [-pqrtx] [-s string] [files ...]\n", command);
	}
	else
	{
		if (ft_strcmp(command, "md5") == 0)
			ft_md5(str, &m);
		else
			ft_sha256(str, &m);
		ft_printhash(str, command, m, flags);
	}
}
