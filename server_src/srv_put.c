/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:37:26 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 14:05:23 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	get_file(int sock, int fd, int nloop)
{
	char	buf[LEN_CHUNCK];
	int		r;
	int		i;

	i = -1;
	while (++i < nloop - 1)
	{
		r = read(sock, buf, LEN_CHUNCK);
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

void	srv_put(int sock, __unused t_data *e)
{
	char	buf[1024];
	int		r;
	int		fd;

	write(sock, "name", 4);
	r = read(sock, buf, 1023);
	buf[r] = '\0';
	if ((fd = open(buf, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		write(sock, "KO", 2);
	else
	{
		write(sock, "OK", 2);
		transfer_file(sock, fd);
		ft_putendl("transfert finish");
		close(fd);
	}
}
