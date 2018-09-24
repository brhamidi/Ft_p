# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 15:36:02 by bhamidi           #+#    #+#              #
#*   Updated: 2018/09/21 19:30:52 by bhamidi          ###   ########.fr       *#
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

CLIENT			= client
CLIENT_PATH		= client_src/
CLIENT_OBJ		= client.o ft_splitwhitespaces.o
CLIENT_OBJS		= $(addprefix $(CLIENT_PATH), $(CLIENT_OBJ))
CLIENT_HEADER	= client.h

LIBNAME	= libft.a
LIBPATH	= ./libft

all: $(LIBNAME) $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(SERVER_PATH)$(SERVER_HEADER) Makefile
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

$(CLIENT): $(CLIENT_OBJS) $(CLIENT_PATH)$(CLIENT_HEADER) Makefile
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@ -L$(LIBPATH) -lft

$(LIBNAME):
	make -C $(LIBPATH)

$(SERVER_PATH)%.o: $(SERVER_PATH)%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(CLIENT_PATH)%.o: $(CLIENT_PATH)%.c
	$(CC) -c $(CFLAGS) -o $@ $< -I$(LIBPATH)

clean: $(SERVER)_clean $(CLIENT)_clean
	make clean -C $(LIBPATH)

$(SERVER)_clean:
	rm -f $(SERVER_OBJS)

$(CLIENT)_clean:
	rm -f $(CLIENT_OBJS)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

.PHONY: all fclean clean re
