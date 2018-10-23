/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:33:38 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 18:10:19 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		get_file_len(const int fd)
{
	struct stat		buf;

	if (fstat(fd, &buf) == -1)
	{
		close(fd);
		return (-1);
	}
	if (buf.st_mode & S_IFDIR)
	{
		close(fd);
		return (-1);
	}
	return (buf.st_size);
}

static void	send_file(int sock, int fd, int nloop)
{
	char	buf[LEN_CHUNCK];
	int		r;
	int		i;

	i = -1;
	while (++i < nloop)
	{
		r = read(fd, buf, LEN_CHUNCK);
		write(sock, buf, r);
		read(sock, buf, 2);
	}
}

static void	transfer_file(int sock, int fd, int file_len)
{
	const int	nloop = (file_len / LEN_CHUNCK) + (file_len % LEN_CHUNCK == 0 ? 0 : 1);
	const char	*snloop = ft_itoa(nloop);
	char		buf[LEN_CHUNCK];

	if (snloop== NULL)
		return;
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
	int			file_len;

	if ((fd = open(*args, O_RDONLY)) == -1
			|| ((file_len = get_file_len(fd)) == -1))
		ft_putendl("ERROR: cannot put the file");
	else
	{
		write(sock, "put", 3);
		r = read(sock, buf, 4);
		write(sock, *args, ft_strlen(*args));
		r = read(sock, buf, 2);
		if (!ft_strncmp("KO", buf, 2))
			ft_putendl("ERROR: cannot put the file");
		else
		{
			transfer_file(sock, fd, file_len);
			ft_putendl("SUCCESS: file has been transfered to the server");
		}
		close(fd);
	}
}
