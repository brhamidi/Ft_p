/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:30:59 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 15:04:31 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	srv_pwd(int sock, t_data *e)
{
	const char *str = ft_strjoin("SUCESS: ", e->pwd);

	write(sock, str, ft_strlen(str));
	free((void *)str);
}
