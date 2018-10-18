/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:48:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 20:28:27 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const char	*success = "SUCCESS: change current directory";
	const char	*error = "ERROR: cannot change directory";

	if (chdir(fullpath) == -1)
		write(sock, error, ft_strlen(error));
	else
	{
		free(e->pwd);
		e->pwd = ft_strdup(path);
		write(sock, success, ft_strlen(success));
	}
	free((void *)fullpath);
}

int		allow(const char *path, int depth)
{
	char	*next;

	if (depth < 0)
		return (0);
	if (! *path)
		return (depth < 0 ? 0 : 1);
	if (*path == '/')
		return allow(path + 1, depth);
	next = ft_strchr(path, '/');
	if (next == NULL)
	{
		if (!ft_strncmp(path, "../", 3) || !ft_strcmp(path, ".."))
			return (depth - 1 < 0 ? 0 : 1);
		return (depth + 1 < 0 ? 0 : 1);
	}
	if (!ft_strncmp(path, "../", 3))
		return (allow(next + 1, depth - 1));
	else
		return (allow(next + 1, depth + 1));
}

void	handle_relatif_path(int sock, t_data *e, char *path)
{
	ft_putendl(path);
	if (allow(path, e->depth))
		write(sock, "path allowed", 12);
	else
		write(sock, "ERROR: path not allowed", 23);
}

void	srv_cd(int sock, t_data *e)
{
	char	buf[1024];
	int		r;

	(void)e;
	write(sock, "run", 3);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		if (r > 1 && buf[r - 1] == '/')
			buf[r - 1] = '\0';
		if (buf[0] == '/')
			handle_abolute_path(sock, e, buf);
		else
			handle_relatif_path(sock, e, buf);
	}
}
