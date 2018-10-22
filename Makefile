# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 20:33:41 by bhamidi           #+#    #+#              #
#    Updated: 2018/10/22 16:38:51 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### GENEREIC ###

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
CFLAGS	+= -O2

################

SERVER			= server
SERVER_PATH		= server_src/
SERVER_OBJ		= server.o server_fork.o srv_ls.o srv_pwd.o environement.o srv_cd.o srv_get.o srv_put.o
SERVER_OBJS		= $(addprefix $(SERVER_PATH), $(SERVER_OBJ))
SERVER_HEADER	= server.h

CLIENT			= client
CLIENT_PATH		= client_src/
CLIENT_OBJ		= client.o array.o cmd_pwd.o cmd_ls.o cmd_cd.o cmd_get.o cmd_put.o
CLIENT_OBJS		= $(addprefix $(CLIENT_PATH), $(CLIENT_OBJ))
CLIENT_HEADER	= client.h

LIBNAME	= libft.a
LIBPATH	= ./libft

all: $(LIBNAME) $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(SERVER_PATH)$(SERVER_HEADER) Makefile
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@ -L$(LIBPATH) -lft

$(CLIENT): $(CLIENT_OBJS) $(CLIENT_PATH)$(CLIENT_HEADER) Makefile
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@ -L$(LIBPATH) -lft

$(LIBNAME):
	@make -C $(LIBPATH)

$(SERVER_PATH)%.o: $(SERVER_PATH)%.c
	$(CC) -c $(CFLAGS) -o $@ $< -I$(LIBPATH)

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
