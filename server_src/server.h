/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:30:22 by bhamidi           #+#    #+#             */
/*   Updated: 2018/10/18 16:02:25 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <fcntl.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include "libft.h"
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>

typedef struct	s_data
{
	char	*root;
	char	*pwd;
	int		depth;
}				t_data;;

int		init(int cs, char **env);
void	srv_ls(int sock, t_data *e);
void	srv_pwd(int sock, t_data *e);
void	clean_e(t_data *e);
void	init_e(t_data *e, char **env, char *userDir);

#endif
