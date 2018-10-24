/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rmdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:24:04 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/24 13:26:06 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	srv_rmdir(char **args, int sock)
{
	char		buf[255];
	int			r;

	write(sock, "rmdir", 5);
	read(sock, buf, 3);
	write(sock, *args, ft_strlen(*args));
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}
