/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:21:49 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 18:44:24 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

const char	*g_cmd_tab[6] = {
	"pwd", "ls", "cd", "get", "put", "mkdir"
};

void		(*g_cmd_func[6])(int, t_data *) = {
	srv_pwd,
	srv_ls,
	srv_cd,
	srv_get,
	srv_put,
	srv_mkdir
};

void	handle_cmd(char *cmd, int sock, t_data *e)
{
	int		i;

	i = -1;
	while (++i < 6)
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

	r = -1;
	if ((r = read(cs, buf, 255)) > 0)
	{
		buf[r] = '\0';
		if (mkdir(buf, 0755) && errno != EEXIST)
			return (-1);
		if (chdir(buf))
			return (-1);
		if (init_e(&e, env, buf) == 0)
			r = repl(cs, &e);
		clean_e(&e);
		return (r);
	}
	return (-1);
}
