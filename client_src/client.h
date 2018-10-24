/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <bhamidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 19:25:24 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/24 13:27:49 by bhamidi          ###   ########.fr       */
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
# include <dirent.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define LEN_CHUNCK		256

int		array_free(char **tab);
size_t	array_len(char **tab);
void	srv_pwd(char **args, int sock);
void	client_pwd(char **args, int sock);
void	srv_ls(char **args, int sock);
void	srv_cd(char **args, int sock);
void	srv_get(char **args, int sock);
void	srv_put(char **args, int sock);
void	srv_rmdir(char **args, int sock);
void	srv_mkdir(char **args, int sock);
void	client_ls(char **args, int sock);
int		cmd_not_exist(char *str);

#endif
