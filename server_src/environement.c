/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:32:50 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/23 17:49:53 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		init_e(t_data *e, char **env, char *userDir)
{
	size_t i;
	size_t len;

	i = 0;
	e->depth = 0;
	if ((e->pwd = ft_strdup("/")) == NULL)
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strlen(env[i]) > 4 && !ft_strncmp("PWD", env[i], 3))
		{
			len = ft_strlen(env[i]) + ft_strlen(userDir) - 4 + 1;
			if ( (e->root = ft_strnew(len + 1)) == NULL)
				return (-1);
			ft_strcpy(e->root, env[i] + 4);
			ft_strcat(e->root, "/");
			ft_strcat(e->root, userDir);
			return (0);
		}
		i++;
	}
	return (1);
}

void	clean_e(t_data *e)
{
	free(e->root);
	free(e->pwd);
}
