/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:28:36 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 12:30:31 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		verifDir(int depth, char *path)
{
	(void)depth;
	(void)path;
	return (1);
}

void	tr_ls_args(int sock, t_data *e, int acc)
{
	char	buf[1024];
	int		r;

	if (acc > 0)
	{
		if ((r = read(sock, buf, 1023)) > 0)
		{
			buf[r] = '\0';
			if (buf[r - 1] == '/')
				buf[r - 1] = '\0';
	//		if (verifDir(e->depth, buf))
	//			ft_putendl("Error: path not authorized");
	//		else
	//			ft_putendl("Sucess: Path Allowed");
			printf("handle %s\n", buf);
		}
		write(sock, "next folder", 11);
		tr_ls_args(sock, e, acc - 1);
	}
}

void	srv_ls(int sock, t_data *e)
{
	char	buf[1024];
	int		r;
	int		nargs;

	write(sock, "ok", 2);
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		nargs = ft_atoi(buf);
		tr_ls_args(sock, e, nargs);
	}
	else
		printf("read() failed with %d\n", r);
}
