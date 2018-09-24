/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/24 19:03:51 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	usage(char *path)
{
	printf("Usage: %s <port>\n", path);
	exit(EXIT_FAILURE);
}

int		create_server(int port)
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
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("bind() failed\n");
		return (-1);
	}
	if (listen(sock, 0x0A) == -1)
	{
		printf("listen() failed\n");
		return (-1);
	}
	return (sock);
}

int		repl(int sock)
{
	int					r;
	char				buf[1024];

	while ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		printf("reveived %d bytes: %s\n", r, buf);
	}
	close(sock);
	return (0);
}

int		handle_clients(int sock)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	pid_t				pid;

	if ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)) == -1)
	{
		printf("accept() failed\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("fork() failed\n");
		return (-1);
	}
	if (pid == 0)
		return (repl(cs));
	else
		return (handle_clients(sock));
}

int		main(int ac, char **av)
{
	int			port;
	int			sock;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	sock = create_server(port);
	if (sock == -1)
	{
		printf("create_server() failed\n");
		exit(EXIT_FAILURE);
	}
	if (handle_clients(sock) == -1)
		printf("handle_clients() failed.\n");
	close(sock);
	return (0);
}
