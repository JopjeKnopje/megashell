# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/07/27 13:31:48 by jboeve        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = app

######################
# OS Dependend flags #
######################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS = -DOS_MAC
endif


RUN_CMD = ./$(NAME)

# CFLAGS += -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address

LIBFT = libft/build/libft.a

INC = -Ilibft/include -Iinclude -I $(shell brew --prefix readline)/include

LFLAGS = -lreadline -L $(shell brew --prefix readline)/lib

SRC_DIR = src
SRCS = main.c

HEADER_DIR = include
HEADERS = megashell.h
OBJ_DIR = obj



SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))


OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJ_DIRS := $(dir $(OBJS))

.PHONY: make_libs

all: make_libs $(NAME)
	$(CC) $(LIBFT) $(CFLAGS) $(INC) $(LFLAGS) src/sender.c -o sender

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(INC) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 


make_libs:
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	$(RUN_CMD)

compile_commands: fclean
	$(MAKE) | compiledb

norm:
	norminette libft include src

dre: re
	$(MAKE) -C libft re
