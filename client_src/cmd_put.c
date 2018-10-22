/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:33:38 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/22 17:29:01 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		get_file_len(const int fd)
{
	struct stat		buf;

	if (fstat(fd, &buf) == -1)
		return (-1);
	if (buf.st_mode & S_IFDIR)
		return (-1);
	return (buf.st_size);
}

static void	send_file(int sock, int fd, int nloop)
{
	char	buf[1024];
	int		r;

	if (nloop == 0)
		return;
	r = read(fd, buf, 1024);
	write(sock, buf, r);
	read(sock, buf, 2);
	send_file(sock, fd, nloop - 1);
}

static void	transfer_file(int sock, int fd, int file_len)
{
	const int	nloop = (file_len / 1024) + (file_len % 1024 == 0 ? 0 : 1);
	const char	*snloop = ft_itoa(nloop);
	char		buf[1024];

	write(sock, snloop, ft_strlen(snloop));
	free((void *)snloop);
	read(sock, buf, 2);
	send_file(sock, fd, nloop);
}

void	srv_put(char **args, int sock)
{
	char		buf[1024];
	int			r;
	int			fd;
	const char	*error = "ERROR: cannot put the file";
	int			file_len;

	if ((fd = open(*args, O_RDONLY)) == -1
			|| ((file_len = get_file_len(fd)) == -1))
		ft_putendl(error);
	else
	{
		write(sock, "put", 3);
		r = read(sock, buf, 4);
		write(sock, *args, ft_strlen(*args));
		r = read(sock, buf, 2);
		if (!ft_strncmp("KO", buf, 2))
			ft_putendl(error);
		else
		{
			transfer_file(sock, fd, file_len);
			ft_putendl("SUCCESS: file has been transfered to the server");
			close(fd);
		}
	}
}
