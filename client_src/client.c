/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:22:53 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/24 19:07:32 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *path)
{
	printf("Usage: %s <server> <port>\n", path);
	exit(EXIT_FAILURE);
}

int		create_client(char *server, char *port)
{
	int			sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
	{
		printf("getprotobyname() failed\n");
		return (-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		printf("socket() failed\n");
		return (-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(port));
	sin.sin_addr.s_addr = inet_addr(server);
	if ((connect(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
	{
		printf("connect() failed\n");
		return (-1);
	}
	return (sock);
}

void	ft_putstr(const char *str)
{
	if (*str)
	{
		write(1, str, 1);
		ft_putstr(str + 1);
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!*s1 || !*s2)
		return (*s1 - *s2);
	if (*s1 == *s2)
		return (ft_strcmp(s1 + 1, s2 + 1));
	return (*s1 - *s2);
}

int		repl(int sock)
{
	char	buf[256];
	int		r;

	ft_putstr("ftp>");
	if ((r = read(0, buf, 255)) > 0)
	{
		buf[r] = '\0';
		if (!ft_strcmp("quit\n", buf))
			return (0);
		write(sock, buf, r);
		return (repl(sock));
	}
	return (0);
}

int		main(int ac, char **av)
{
	int	sock;

	if (ac != 3)
		usage(av[0]);
	if ((sock = create_client(av[1], av[2])) == -1)
	{
		printf("create_client() failed\n");
		exit(EXIT_FAILURE);
	}
	if (repl(sock))
		printf("repl() failed.\n");
	close(sock);
	return (0);
}
