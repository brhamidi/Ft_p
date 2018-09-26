/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/26 19:51:54 by bhamidi          ###   ########.fr       */
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
		perror("getprotobyname() failed");
		return (-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		perror("socket() failed");
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
		perror("listen() failed");
		return (-1);
	}
	return (sock);
}

int		repl(int sock, t_data *e)
{
	int					r;
	char				buf[1024];

	(void)e;
	while ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		printf("reveived %d bytes: %s\n", r, buf);
	}
	close(sock);
	return (0);
}

void	init_e(t_data *e, char **env, char *userDir)
{
	size_t i;
	size_t len;

	i = 0;
	e->pwd = ft_strdup("/");
	while (env[i] != NULL)
	{
		if (ft_strlen(env[i]) > 4 && !ft_strncmp("PWD", env[i], 3))
		{
			len = ft_strlen(env[i]) + ft_strlen(userDir) - 4 + 1;
			e->root = ft_strnew(len + 1);
			ft_strcpy(e->root, env[i] + 4);
			ft_strcat(e->root, "/");
			ft_strcat(e->root, userDir);
			printf("root: %s\n", e->root);
			printf("pwd: %s\n", e->pwd);
		}
		i++;
	}
}

void	clean_e(t_data *e)
{
	free(e->root);
	free(e->pwd);
}

int		init(int cs, char **env)
{
	int		r;
	char	buf[255];
	t_data	e;

	if ((r = read(cs, buf, 255)) > 0)
	{
		buf[r] = '\0';
		if (mkdir(buf, 0755) && errno != EEXIST)
		{
			perror("mkdir() failed");
			return (-1);
		}
		if (chdir(buf))
		{
			perror("chdir() failed");
			return (-1);
		}
		init_e(&e, env, buf);
		r = repl(cs, &e);
		clean_e(&e);
		return (r);
	}
	return (-1);
}

int		handle_clients(int sock, char **env)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	pid_t				pid;

	if ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)) == -1)
	{
		perror("accept() failed");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork() failed");
		return (-1);
	}
	if (pid == 0)
	{
		if (init(cs, env) == -1)
			return (-1);
		close(cs);
		return (0);
	}
	else
		return (handle_clients(sock, env));
}

int		main(int ac, char **av, char **env)
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
	if (handle_clients(sock, env) == -1)
	{
		printf("handle_clients() failed.\n");
		exit(EXIT_FAILURE);
	}
	close(sock);
	return (0);
}
