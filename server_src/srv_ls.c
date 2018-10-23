/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:28:36 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:45:47 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*join(char **result, char *name)
{
	const int	len = ft_strlen(*result) + ft_strlen(name) + 1;
	char		*res;

	res = ft_strnew(len + 1);
	if (res == NULL)
		return (NULL);
	ft_strcpy(res, *result);
	ft_strcat(res, " ");
	ft_strcat(res, name);
	free(*result);
	return (res);
}

void		srv_ls(int sock, t_data *e)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*result;

	(void)e;
	dirp = opendir(".");
	if ((result = ft_strdup("SUCCESS:")) == NULL)
		return ;
	if (dirp == NULL)
		write(sock, "ERROR: cannot open current server directory", 37);
	else
	{
		while ((dp = readdir(dirp)) != NULL)
			if ((result = join(&result, dp->d_name)) == NULL)
				return ;
		write(sock, result, ft_strlen(result));
	}
	free(result);
	(void)closedir(dirp);
}
