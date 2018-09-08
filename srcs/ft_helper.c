/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:14:01 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 12:36:26 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ssl.h"

char	*ft_fdtostr(int fd)
{
	int		ret;
	char	*tmp;
	char	*str;
	char	buff[BUFFSIZE];

	str = ft_strnew(0);
	while ((ret = read(fd, &buff, BUFFSIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(str, buff);
		free(str);
		str = tmp;
	}
	return (str);
}

int		ft_checkfile(char *command, char *arg)
{
	int fd;

	if ((fd = open(arg, O_RDONLY)) == -1)
		ft_printf("%s: %s: No such file or directory\n", command, arg);
	return (fd);
}

char	*str_toupper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (str);
}

char	*str_tolower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}
