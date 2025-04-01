# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhara <nhara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:12:00 by nhara             #+#    #+#              #
#    Updated: 2025/04/01 15:04:58 by nhara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ファイル名
CLIENT = client
SERVER = server

# ソースとオブジェクトファイル
SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

HEADER = minitalk.h

LIBFT = libft/libft.a
LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(CLIENT) $(SERVER)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -L$(LIBFT_DIR) -lft -o $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -L$(LIBFT_DIR) -lft -o $(SERVER)

# コンパイルルール（.c → .o）
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
