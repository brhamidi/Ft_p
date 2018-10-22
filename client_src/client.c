/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:22:53 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/22 16:33:29 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *path)
{
	printf("Usage: %s <server> <port> [ directory ]\n", path);
	exit(EXIT_FAILURE);
}

const char	*g_cmd_tab[9] = {
	"pwd", "lpwd", "ls", "lls", "cd", "get", "put", "quit"
};

int		cmdNotExist(char *str)
{
	int		i;

	i = -1;
	while (++i < 8)
		if (!ft_strcmp(g_cmd_tab[i], str))
			return (0);
	return (1);
}

int		allowCmd(char **array)
{
	if (!array || !*array)
		return (-1);
	if (cmdNotExist(*array))
		return (1);
	if (!ft_strcmp(*array, "pwd") || !ft_strcmp(*array, "quit") ||
			!ft_strcmp(*array, "lpwd") || !ft_strcmp(*array, "ls")
			|| !ft_strcmp(*array, "lls"))
		if (array_len(array) > 1)
			return (2);
	if (!ft_strcmp(*array, "get") || !ft_strcmp(*array, "put")
			|| !ft_strcmp(*array, "cd"))
	{
		if (array_len(array) > 2)
			return (2);
		if (array_len(array) < 2)
			return (3);
	}
	return (0);
}

const char	*g_error[3] = {
	"command not found",
	"too much argument",
	"argument not found"
};

void		(*g_cmd_func[8])(char **, int) = {
	srv_pwd,
	client_pwd,
	srv_ls,
	client_ls,
	srv_cd,
	srv_get,
	srv_put
};

void	handle_cmd(char *cmd, char **argvs, int sock)
{
	int		i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(cmd, g_cmd_tab[i]))
			g_cmd_func[i](argvs, sock);
}

int		repl(int sock)
{
	char	buf[1024];
	int		r;
	char	**array;

	ft_putstr("ftp>");
	if ((r = read(0, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		if ((array = ft_splitwhitespaces(buf)) != NULL)
		{
			if ((r = allowCmd(array)))
				printf("ERROR: %s\n", g_error[r - 1]);
			else if (!ft_strcmp("quit", array[0]))
				return (array_free(array));
			else
				handle_cmd(*array, array + 1, sock);
			array_free(array);
		}
		return (repl(sock));
	}
	return (0);
}

int		create_client(char *server, char *port)
{
	int			sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
	{
		perror("getprotobyname() failed");
		return (-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		perror("socket() failed");
		return (-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(port));
	sin.sin_addr.s_addr = inet_addr(server);
	if ((connect(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
	{
		perror("connect() failed");
		return (-1);
	}
	return (sock);
}

int		main(int ac, char **av)
{
	int		sock;
	char	*dir;

	if (ac < 3 || ac > 4)
		usage(av[0]);
	if ((sock = create_client(av[1], av[2])) == -1)
	{
		printf("create_client() failed\n");
		exit(EXIT_FAILURE);
	}
	dir = ac == 3 ? "guest" : av[3];
	write(sock, dir, ft_strlen(dir));
	if (repl(sock))
		printf("repl() failed.\n");
	close(sock);
	return (0);
}
