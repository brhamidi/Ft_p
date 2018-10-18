/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:28:36 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 16:42:58 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*join(char **result, char *name)
{
	const int	len = ft_strlen(*result) + ft_strlen(name) + 1;
	char		*res;
	
	res = ft_strnew(len + 1);
	ft_strcpy(res, *result);
	ft_strcat(res, " ");
	ft_strcat(res, name);
	free(*result);
	return (res);
}

void	srv_ls(int sock, t_data *e)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*result;

	(void)e;
	dirp = opendir(".");
	result = ft_strdup("SUCCESS:");
	if (dirp == NULL)
		write(sock, "ERROR: cannot open current server directory", 37);
	else
	{
		while ((dp = readdir(dirp)) != NULL)
			result = join(&result, dp->d_name);
		write(sock, result, ft_strlen(result));
	}
	free(result);
	(void)closedir(dirp);
}
