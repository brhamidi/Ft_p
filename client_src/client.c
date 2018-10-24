/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:22:53 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/24 13:34:00 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		allow_cmd(char **array)
{
	if (!array || !*array)
		return (-1);
	if (cmd_not_exist(*array))
		return (1);
	if (!ft_strcmp(*array, "pwd") || !ft_strcmp(*array, "quit") ||
			!ft_strcmp(*array, "lpwd") || !ft_strcmp(*array, "ls")
			|| !ft_strcmp(*array, "lls"))
		if (array_len(array) > 1)
			return (2);
	if (!ft_strcmp(*array, "get") || !ft_strcmp(*array, "put")
			|| !ft_strcmp(*array, "cd") || !ft_strcmp(*array, "mkdir")
			|| !ft_strcmp(*array, "rmdir"))
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

void		(*g_cmd_func[10])(char **, int) = {
	srv_pwd,
	client_pwd,
	srv_ls,
	client_ls,
	srv_cd,
	srv_get,
	srv_put,
	srv_mkdir,
	srv_rmdir
};

void	handle_cmd(char *cmd, char **argvs, int sock)
{
	int			i;
	const char	*cmd_tab[10] = {
		"pwd", "lpwd", "ls", "lls", "cd", "get", "put", "mkdir", "rmdir", "quit"
	};

	i = -1;
	while (++i < 9)
		if (!ft_strcmp(cmd, cmd_tab[i]))
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
			if ((r = allow_cmd(array)))
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
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				*srv;

	srv = (!ft_strcmp(server, "localhost")) ? "127.0.0.1" : server;
	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(port));
	sin.sin_addr.s_addr = inet_addr(srv);
	if ((connect(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
		return (-1);
	return (sock);
}

int		main(int ac, char **av)
{
	int		sock;
	char	*dir;

	if (ac < 3 || ac > 4)
	{
		printf("Usage: %s <server> <port> [ directory ]\n", av[0]);
		exit(EXIT_FAILURE);
	}
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
