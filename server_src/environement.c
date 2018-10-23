/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:32:50 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:50:39 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		get_depth(const char *path, int curr_depth, int acc)
{
	char	*next;

	if (path == NULL || !*path)
		return (acc + curr_depth < 0 ? -1 : acc + curr_depth);
	if (*path == '/')
		return (get_depth(path + 1, curr_depth, acc));
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
		return (acc - 1 + curr_depth < 0 ? -1
				: get_depth(next + 1, curr_depth, acc - 1));
	else if (!ft_strncmp(path, "./", 2))
		return (get_depth(next + 1, curr_depth, acc));
	return (get_depth(next + 1, curr_depth, acc + 1));
}

int		init_e(t_data *e, char **env, char *user_dir)
{
	size_t i;
	size_t len;

	i = 0;
	e->depth = 0;
	if ((e->pwd = ft_strdup("/")) == NULL)
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strlen(env[i]) > 4 && !ft_strncmp("PWD", env[i], 3))
		{
			len = ft_strlen(env[i]) + ft_strlen(user_dir) - 4 + 1;
			if ((e->root = ft_strnew(len + 1)) == NULL)
				return (-1);
			ft_strcpy(e->root, env[i] + 4);
			ft_strcat(e->root, "/");
			ft_strcat(e->root, user_dir);
			return (0);
		}
		i++;
	}
	return (1);
}

void	clean_e(t_data *e)
{
	free(e->root);
	free(e->pwd);
}
