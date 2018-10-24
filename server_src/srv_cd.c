/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:48:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/24 13:16:19 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handle_abolute_path(int sock, t_data *e, char *path)
{
	const char	*fullpath = ft_strjoin(e->root, path);
	const int	path_depth = get_depth(path, 0, 0);
	const char	*success = "SUCCESS: change current directory";
	const char	*error = "ERROR: cannot change directory";
	const char	*error_depth = "ERROR: path not allowed";

	if (fullpath == NULL)
		return ;
	if (path_depth == -1)
		write(sock, error_depth, ft_strlen(error_depth));
	else if (chdir(fullpath) == -1)
		write(sock, error, ft_strlen(error));
	else
	{
		free(e->pwd);
		if ((e->pwd = ft_strdup(path)) == NULL)
			return ;
		e->depth = path_depth;
		write(sock, success, ft_strlen(success));
	}
	free((void *)fullpath);
}

char	*compute(const char **array, int index, char *buf, int skip)
{
	if (index < 0)
		return (buf);
	if (!ft_strcmp(array[index], ".."))
		return (compute(array, index - 1, buf, skip + 1));
	if (!ft_strcmp(array[index], "."))
		return (compute(array, index - 1, buf, skip));
	if (skip > 0)
		return (compute(array, index - 1, buf, skip - 1));
	else
	{
		compute(array, index - 1, buf, skip);
		ft_strcat(buf, "/");
		ft_strcat(buf, array[index]);
	}
	return (buf);
}

void	clean_path(char **path, int depth)
{
	const char	**array = (const char **)ft_strsplit(*path, '/');
	char		*res;

	if (array == NULL)
		return ;
	if (depth != 0)
	{
		if ((res = ft_strnew(ft_strlen(*path) + 1)) == NULL)
			return ;
		res = compute(array, array_len((char**)array) - 1, res, 0);
	}
	else
	{
		if ((res = ft_strdup("/")) == NULL)
			return ;
	}
	free(*path);
	*path = res;
	array_free((char **)array);
}

void	handle_relatif_path(int sock, t_data *e, char *path)
{
	const char	*error = "ERROR: cannot change directory";
	char		*tmp;

	if (get_depth(path, e->depth, 0) == -1)
		write(sock, "ERROR: path not allowed", 23);
	else
	{
		if (chdir(path) == -1)
			write(sock, error, ft_strlen(error));
		else
		{
			e->depth = get_depth(path, e->depth, 0);
			tmp = e->pwd;
			if ((e->pwd = ft_strnew(ft_strlen(e->pwd) +
							ft_strlen(path) + 1 + 2)) == NULL)
				return ;
			ft_strcpy(e->pwd, tmp);
			ft_strcat(e->pwd, "/");
			ft_strcat(e->pwd, path);
			clean_path(&e->pwd, e->depth);
			free(tmp);
			write(sock, "SUCCESS: change current directory", 33);
		}
	}
}

void	srv_cd(int sock, t_data *e)
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
