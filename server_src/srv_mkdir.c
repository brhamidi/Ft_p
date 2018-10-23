/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_mkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:47:12 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:51:09 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const int	path_depth = get_depth(path, 0, 0);
	const char	*success = "SUCCESS: create directory";
	const char	*error = "ERROR: cannot create directory";
	const char	*error_depth = "ERROR: path not allowed";

	if (fullpath == NULL)
		return ;
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

void		srv_mkdir(int sock, t_data *e)
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
