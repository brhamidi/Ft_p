/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:29:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/24 13:25:37 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		cmd_not_exist(char *str)
{
	int			i;
	const char	*cmd_tab[10] = {
		"pwd", "lpwd", "ls", "lls", "cd", "get", "put", "mkdir", "rmdir", "quit"
	};

	i = -1;
	while (++i < 9)
		if (!ft_strcmp(cmd_tab[i], str))
			return (0);
	return (1);
}

size_t	array_len(char **tab)
{
	size_t	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

int		array_free(char **tab)
{
	size_t	n;

	n = 0;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	free(tab);
	return (0);
}
