/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:30:22 by bhamidi           #+#    #+#             */
/*   Updated: 2018/09/26 19:15:03 by bhamidi          ###   ########.fr       */
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

typedef struct	s_data
{
	char	*root;
	char	*pwd;
}				t_data;;

#endif
