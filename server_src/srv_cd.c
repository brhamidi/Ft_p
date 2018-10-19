/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:48:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/19 12:42:39 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		get_depth(const char *path)
{
	char	*next;

	if (path == NULL || ! *path)
		return (0);
	if (*path == '/')
		return get_depth(path + 1);
	next = ft_strchr(path, '/');
	if (next == NULL)
	{
		if (!ft_strncmp(path, "../", 3) || !ft_strcmp(path, ".."))
			return (-1);
		return (1);
	}
	if (!ft_strncmp(path, "../", 3))
		return (get_depth(next + 1) - 1);
	else
		return (1 + get_depth(next + 1));
}

void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const int	path_depth = get_depth(fullpath);
	const char	*success = "SUCCESS: change current directory";
	const char	*error = "ERROR: cannot change directory";

	if (chdir(fullpath) == -1)
		write(sock, error, ft_strlen(error));
	else
	{
		free(e->pwd);
		e->pwd = ft_strdup(path);
		e->depth = path_depth;
		write(sock, success, ft_strlen(success));
	}
	free((void *)fullpath);
}

void	handle_relatif_path(int sock, t_data *e, char *path)
{
	const int path_depth = get_depth(path);


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
