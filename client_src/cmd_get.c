/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:25:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:10:34 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	get_file(int sock, int fd, int nloop)
{
	char	buf[1024];
	int		r;
	int		i;

	i = -1;
	while (++i < nloop)
	{
		r = read(sock, buf, 1024);
		write(fd, buf, r);
		write(sock, "OK", 2);
	}
}

static void	transfer_file(int sock, int fd)
{
	char	buf[1024];
	int		r;

	r = read(sock, buf, 1023);
	buf[r] = '\0';
	write(sock, "go", 2);
	get_file(sock, fd, ft_atoi(buf));
}

void		srv_get(char **args, int sock)
{
	char		buf[1024];
	int			r;
	int			fd;

	write(sock, "get", 3);
	r = read(sock, buf, 4);
	write(sock, *args, ft_strlen(*args));
	r = read(sock, buf, 2);
	if (!ft_strncmp("KO", buf, 2))
		ft_putendl("ERROR: cannot get the file");
	else
	{
		if ((fd = open(*args, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			write(sock, "KO", 2);
			ft_putendl("ERROR: cannot get the file");
		}
		else
		{
			write(sock, "OK", 3);
			transfer_file(sock, fd);
			ft_putendl("SUCCESS: file has been transfered from the server");
			close(fd);
		}
	}
}
