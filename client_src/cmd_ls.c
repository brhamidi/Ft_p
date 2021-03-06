/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:35:48 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 19:17:54 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static char	*join(char **result, char *name)
{
	const int	len = ft_strlen(*result) + ft_strlen(name) + 1;
	char		*res;

	res = ft_strnew(len + 1);
	ft_strcpy(res, *result);
	if (res == NULL)
		return (NULL);
	ft_strcat(res, " ");
	ft_strcat(res, name);
	free(*result);
	return (res);
}

void		client_ls(char **args, int sock)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*result;

	(void)sock;
	(void)args;
	dirp = opendir(".");
	if (dirp == NULL)
	{
		ft_putendl("ERROR: cannot open current directory");
		return ;
	}
	if ((result = ft_strdup("SUCCESS:")) == NULL)
		return ;
	while ((dp = readdir(dirp)) != NULL)
		if ((result = join(&result, dp->d_name)) == NULL)
			return ;
	ft_putendl(result);
	free(result);
	(void)closedir(dirp);
}

void		srv_ls(char **args, int sock)
{
	char		buf[255];
	int			r;

	(void)args;
	write(sock, "ls", 2);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}
