/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:27:30 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:25:01 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	get_file_len(const int fd)
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
	int		i;

	i = 0;
	while (i < nloop)
	{
		r = read(fd, buf, 1024);
		write(sock, buf, r);
		read(sock, buf, 2);
		i++;
	}
}

static void	transfer_file(int sock, int fd, int file_len)
{
	const int	nloop = (file_len / 1024) + (file_len % 1024 == 0 ? 0 : 1);
	const char	*snloop = ft_itoa(nloop);
	char		buf[1024];

	if (snloop == NULL)
		return ;
	write(sock, snloop, ft_strlen(snloop));
	free((void *)snloop);
	read(sock, buf, 2);
	send_file(sock, fd, nloop);
}

void		srv_get(int sock, t_data *e)
{
	char	buf[1024];
	int		r;
	int		fd;
	int		file_len;

	(void)e;
	write(sock, "name", 4);
	r = read(sock, buf, 1023);
	buf[r] = '\0';
	if ((fd = open(buf, O_RDONLY)) == -1)
		write(sock, "KO", 2);
	else
	{
		if ((file_len = get_file_len(fd)) == -1)
			write(sock, "KO", 2);
		else
		{
			write(sock, "OK", 2);
			r = read(sock, buf, 2);
			if (!ft_strncmp("OK", buf, 2))
				transfer_file(sock, fd, file_len);
		}
		close(fd);
	}
}
