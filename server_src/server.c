/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/28 20:02:25 by bhamidi          ###   ########.fr       */
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
	int					sock;
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

void	init_e(t_data *e, char **env, char *userDir)
{
	size_t i;
	size_t len;

	i = 0;
	e->depth = 0;
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
			printf("depth: %d\n", e->depth);
		}
		i++;
	}
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*str;
	const size_t	len = ft_strlen(s1) + ft_strlen(s2);

	if (!s1 || !s2)
		return (NULL);
	if ((str = ft_strnew(len + 1)) == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}

void	clean_e(t_data *e)
{
	free(e->root);
	free(e->pwd);
}

int		verifDir(int depth, char *path)
{
	(void)depth;
	(void)path;
	return (1);
}

void	tr_ls_args(int sock, t_data *e, int acc)
{
	char	buf[1024];
	int		r;

	if (acc > 0)
	{
		if ((r = read(sock, buf, 1023)) > 0)
		{
			buf[r] = '\0';
			if (buf[r - 1] == '/')
				buf[r - 1] = '\0';
	//		if (verifDir(e->depth, buf))
	//			ft_putendl("Error: path not authorized");
	//		else
	//			ft_putendl("Sucess: Path Allowed");
			printf("handle %s\n", buf);
		}
		write(sock, "next folder", 11);
		tr_ls_args(sock, e, acc - 1);
	}
}

void	srv_ls(int sock, t_data *e)
{
	char	buf[1024];
	int		r;
	int		nargs;

	write(sock, "ok", 2);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		nargs = ft_atoi(buf);
		tr_ls_args(sock, e, nargs);
	}
	else
		printf("read() failed with %d\n", r);
}

void	srv_pwd(int sock, t_data *e)
{
	char *str = ft_strjoin("SUCESS: ", e->pwd);

	write(sock, str, ft_strlen(str));
	free(str);
}

const char	*g_cmd_tab[5] = {
	"pwd", "ls", "cd", "get", "put"
};

void		(*g_cmd_func[5])(int, t_data *) = {
	srv_pwd,
	srv_ls
};

void	handle_cmd(char *cmd, int sock, t_data *e)
{
	int		i;

	i = -1;
	while (++i < 5)
		if (!ft_strcmp(cmd, g_cmd_tab[i]))
			g_cmd_func[i](sock, e);
}

int		repl(int sock, t_data *e)
{
	int					r;
	char				buf[1024];

	while ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		handle_cmd(buf, sock, e);
	}
	close(sock);
	return (0);
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
