/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_mkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:47:12 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:03:12 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		get_depth(const char *path, int curr_depth, int acc)
{
	char	*next;

	if (path == NULL || ! *path)
		return (acc + curr_depth < 0 ? -1 : acc + curr_depth);
	if (*path == '/')
		return get_depth(path + 1, curr_depth, acc);
	next = ft_strchr(path, '/');
	if (next == NULL)
	{
		if (!ft_strcmp(path, ".."))
			return ((acc - 1 + curr_depth < 0) ? -1 : acc - 1 + curr_depth);
		else if (!ft_strcmp(path, "."))
			return (acc + curr_depth);
		return (acc + 1 + curr_depth);
	}
	if (!ft_strncmp(path, "../", 3))
		return (acc - 1 + curr_depth < 0 ? -1 : get_depth(next + 1, curr_depth, acc - 1));
	else if (!ft_strncmp(path, "./", 2))
		return (get_depth(next + 1, curr_depth, acc));
	return (get_depth(next + 1, curr_depth, acc + 1));
}

static void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const int	path_depth = get_depth(path, 0, 0);
	const char	*success = "SUCCESS: create directory";
	const char	*error = "ERROR: cannot create directory";
	const char	*error_depth = "ERROR: path not allowed";

	if (fullpath == NULL)
		return;
	if (path_depth == -1)
		write(sock, error_depth, ft_strlen(error_depth));
	else if (mkdir(fullpath, 0755) == -1)
		write(sock, error, ft_strlen(error));
	else
		write(sock, success, ft_strlen(success));
	free((void *)fullpath);
}

static void	handle_relatif_path(int sock, t_data *e, char *path)
{
	const int	path_depth = get_depth(path, e->depth, 0);
	const char	*success = "SUCCESS: create directory";
	const char	*error = "ERROR: cannot create directory";
	const char	*error_depth = "ERROR: path not allowed";

	if (path_depth == -1)
		write(sock, error_depth, ft_strlen(error_depth));
	else
	{
		if (mkdir(path, 0755) == -1)
			write(sock, error, ft_strlen(error));
		else
			write(sock, success, ft_strlen(success));
	}
}

void	srv_mkdir(int sock, t_data *e)
{
	char	buf[1024];
	int		r;

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
