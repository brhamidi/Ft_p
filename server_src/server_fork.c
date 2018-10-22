/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:21:49 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/22 13:26:50 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

const char	*g_cmd_tab[5] = {
	"pwd", "ls", "cd", "get", "put"
};

void		(*g_cmd_func[5])(int, t_data *) = {
	srv_pwd,
	srv_ls,
	srv_cd,
	srv_get
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
		// log
			printf("\nroot: %s\n", e->root);
			printf("pwd: %s\n", e->pwd);
			printf("depth: %d\n", e->depth);
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
