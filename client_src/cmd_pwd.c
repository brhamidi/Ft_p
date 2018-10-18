/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:34:13 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 13:35:37 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

extern char **environ;

void	client_pwd(char **args, int sock)
{
	(void)args;
	(void)sock;
	int  i;

	i = -1;
	while (environ[++i])
		if (!ft_strncmp(environ[i], "PWD=", 4))
		{
			printf("SUCESS: %s\n", environ[i] + 4);
			return;
		}
	ft_putendl_fd("ERROR: $PWD not set", 2);
}

void	srv_pwd(char **args, int sock)
{
	int		r;
	char	buf[1024];

	(void)args;
	write(sock, "pwd", 3);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}
