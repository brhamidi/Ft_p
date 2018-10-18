/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:50:32 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 20:14:10 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	srv_cd(__unused char **args, int sock)
{
	char		buf[255];
	int			r;

	write(sock, "cd", 2);
	read(sock, buf, 3);
	write(sock, *args, ft_strlen(*args));
	if ((r = read(sock, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf);
	}
}
