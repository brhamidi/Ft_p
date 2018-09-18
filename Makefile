# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 15:36:02 by bhamidi           #+#    #+#              #
#    Updated: 2018/09/18 16:05:17 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### GENEREIC ###

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -O2

################

SERVER			= server
SERVER_PATH		= server/
SERVER_SRC		= server.c
SERVER_OBJ		= $(SERVER:.c=.o)
SERVER_HEADER	= server.h

all: $(SERVER)

$(SERVER): $(SERVER_PATH)$(SERVER_OBJ) $(SERVER_PATH)$(SERVER_HEADER) Makefile
	@echo "Ready for compile."

$(SERVER_PATH)%.o: $(SERVER_PATH)%.c
	$(CC) -c $(CFLAGS) $<
