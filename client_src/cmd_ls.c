/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:35:48 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 13:36:12 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	srv_ls(char **args, int sock)
{
	const int	len = array_len(args);
	const char	*slen = ft_itoa(len);
	char		buf[255];
	int		i;

	write(sock, "ls", 2);
	read(sock, buf, 2);
	write(sock, slen, ft_strlen(slen));
	free((void *)slen);
	i = -1;
	while (++i < len)
	{
		write(sock, args[i], ft_strlen(args[i]));
		read(sock, buf, 255);
	}
}
