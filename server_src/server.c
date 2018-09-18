/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/18 17:22:48 by bhamidi          ###   ########.fr       */
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
	int				sock;
	struct protoent	*proto;
	
	(void)port;
	proto = getprotobyname("tcp");
	if (!proto)
	{
		printf("getprotobyname() failed\n");
		return (-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
	{
		printf("socket() failed\n");
		return (-1);
	}
	return (sock);
}

int		main(int ac, char **av)
{
	int		port;
	int		sock;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	sock = create_server(port);
	if (sock == -1)
	{
		printf("create_server() failed\n");
		exit(EXIT_FAILURE);
	}
	close(sock);
	return (0);
}
