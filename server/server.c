/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:29:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/18 15:35:31 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	usage(char *path)
{
	printf("Usage: %s <port>\n", path);
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		usage(av[0]);
	;
}
