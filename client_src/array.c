/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:29:15 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/22 13:30:07 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
