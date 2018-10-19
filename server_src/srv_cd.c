/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:48:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/19 15:38:26 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		get_depth(const char *path, int curr_depth, int acc)
{
	char	*next;

	if (path == NULL || ! *path)
		return (acc);
	if (*path == '/')
		return get_depth(path + 1, curr_depth, acc);
	next = ft_strchr(path, '/');
	if (next == NULL)
	{
		if (!ft_strncmp(path, "../", 3) || !ft_strcmp(path, ".."))
			return ((acc - 1 + curr_depth < 0) ? -1 : acc - 1);
		return (acc + 1);
	}
	if (!ft_strncmp(path, "../", 3))
		return (acc - 1 + curr_depth < 0 ? -1 : get_depth(next + 1, curr_depth, acc - 1));
	else
		return (get_depth(next + 1, curr_depth, acc + 1));
}

void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const int	path_depth = get_depth(path, 0, 0);
	const char	*success = "SUCCESS: change current directory";
	const char	*error = "ERROR: cannot change directory";
	const char	*error_depth = "ERROR: path not allowed";

	if (path_depth == -1)
		write(sock, error_depth, ft_strlen(error_depth));
	else if (chdir(fullpath) == -1)
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
	const int	path_depth = get_depth(path, e->depth, 0);
	const char	*success = "SUCCESS: change current directory";
	const char	*error = "ERROR: cannot change directory";
	const char	*error_depth = "ERROR: path not allowed";
	char		*tmp;

	if (path_depth == -1)
		write(sock, error_depth, ft_strlen(error_depth));
	else
	{
		if (chdir(path) == -1)
			write(sock, error, ft_strlen(error));
		else
		{
			e->depth = path_depth;
			tmp = e->pwd;
			e->pwd = ft_strjoin(e->pwd, path);
			free(tmp);
			write(sock, success, ft_strlen(success));
		}
	}
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
