/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:48:08 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 18:54:34 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	srv_mkdir(char **args, int sock)
{
	char		buf[255];
	int			r;

	write(sock, "mkdir", 5);
	read(sock, buf, 3);
	write(sock, *args, ft_strlen(*args));
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}
