# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 15:36:02 by bhamidi           #+#    #+#              #
#    Updated: 2018/09/18 17:10:16 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### GENEREIC ###

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -O2

################

SERVER			= server
SERVER_PATH		= server_src/
SERVER_OBJ		= server.o
SERVER_OBJS		= $(addprefix $(SERVER_PATH), $(SERVER_OBJ))
SERVER_HEADER	= server.h

all: $(SERVER)

$(SERVER): $(SERVER_OBJS) $(SERVER_PATH)$(SERVER_HEADER) Makefile
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

$(SERVER_PATH)%.o: $(SERVER_PATH)%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean: $(SERVER)_clean

$(SERVER)_clean:
	rm -f $(SERVER_OBJS)

fclean: clean
	rm -f $(SERVER)

re: fclean all

.PHONY: all fclean clean re
