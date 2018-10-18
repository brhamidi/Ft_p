/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:25:24 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 13:36:17 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <fcntl.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "libft.h"
# include <errno.h>

void	array_free(char **tab);
size_t	array_len(char **tab);
void	srv_pwd(char **args, int sock);
void	client_pwd(char **args, int sock);
void	srv_ls(char **args, int sock);

#endif
