/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:22:53 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/21 23:12:18 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *path)
{
	printf("Usage: %s <server> <port>\n", path);
}

int	create_client(char *server, char *port)
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
		printf("connect() failed\n");
	return (sock);
}

int	main(int ac, char **av)
{
	int	sock;

	if (ac != 3)
		usage(av[0]);
	if ((sock = create_client(av[1], av[2])) == -1)
	{
		printf("create_client() failed\n");
		exit(EXIT_FAILURE);
	}
	if (write(sock, "42born\n", 7) == -1)
		printf("write() failed\n");
	close(sock);
	return (0);
}
