# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhara <nhara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:12:00 by nhara             #+#    #+#              #
#    Updated: 2025/04/02 18:11:41 by nhara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_CLIENT = client.c
SRC_SERVER = server.c

LIBFT_DIR = libft
LIBFT =$(LIBFT_DIR)/libft.a

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

HEADER = minitalk.h

all: $(LIBFT) $(CLIENT) $(SERVER)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT) -L$(LIBFT_DIR) -lft

$(SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_SERVER) -L$(LIBFT_DIR) -lft

bonus : all

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	
fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
