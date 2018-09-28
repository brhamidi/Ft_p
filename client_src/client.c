/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:22:53 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/28 20:00:43 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *path)
{
	printf("Usage: %s <server> <port> [ directory ]\n", path);
	exit(EXIT_FAILURE);
}

size_t	array_len(char **tab)
{
	size_t	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

void	array_free(char **tab)
{
	size_t	n;

	n = 0;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	free(tab);
}

const char	*g_error[3] = {
	"command not found",
	"too much argument",
	"argument not found"
};

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
			!ft_strcmp(*array, "lpwd"))
		if (array_len(array) > 1)
			return (2);
	if (!ft_strcmp(*array, "get") || !ft_strcmp(*array, "put"))
	{
		if (array_len(array) > 2)
			return (2);
		if (array_len(array) < 2)
			return (3);
	}
	return (0);
}

extern char **environ;

void	client_pwd(char **args, int sock)
{
	(void)args;
	(void)sock;
	int  i;

	i = -1;
	while (environ[++i])
		if (!ft_strncmp(environ[i], "PWD=", 4))
		{
			printf("SUCESS: %s\n", environ[i] + 4);
			return;
		}
	ft_putendl_fd("ERROR: $PWD not set", 2);
}

void	srv_pwd(char **args, int sock)
{
	int		r;
	char	buf[1024];

	(void)args;
	write(sock, "pwd", 3);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}

void	srv_ls(char **args, int sock)
{
	const int	len = array_len(args);
	const char	*slen = ft_itoa(len);
	char		buf[255];

	write(sock, "ls", 2);
	read(sock, buf, 2);
	write(sock, slen, ft_strlen(slen));
	free((void *)slen);
}

void		(*g_cmd_func[8])(char **, int) = {
	srv_pwd,
	client_pwd,
	srv_ls
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
				return (0);
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

void	init(char *dir, int sock)
{
	write(sock, dir, ft_strlen(dir));
}

int		main(int ac, char **av)
{
	int	sock;

	if (ac < 3 || ac > 4)
		usage(av[0]);
	if ((sock = create_client(av[1], av[2])) == -1)
	{
		printf("create_client() failed\n");
		exit(EXIT_FAILURE);
	}
	init(ac == 3 ? "guest" : av[3], sock);
	if (repl(sock))
		printf("repl() failed.\n");
	close(sock);
	return (0);
}
