# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/08/18 23:25:59 by joppe         ########   odam.nl          #
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
	I_RL = -I $(shell brew --prefix readline)/include
	L_RL = -L $(shell brew --prefix readline)/lib
	CFLAGS = -DOS_MAC
endif


RUN_CMD = ./$(NAME)

# CFLAGS += -Wall -Wextra -Werror
CFLAGS += -Wall -Wextra
CFLAGS += -g -fsanitize=address

LIBFT = libft/build/libft.a

INC = -Ilibft/include -Iinclude $(I_RL)
LFLAGS = -lreadline $(L_RL)

SRC_DIR = src
SRCS =	input/prompt.c \
	  	input/signals.c \
	  	input/history_file.c \
	  	plarser/lexer.c \
	  	plarser/lexer_list.c \
	  	plarser/lexer_utils.c \
	  	plarser/plarser.c \
	  	plarser/syntax.c \
	  	plarser/syntax_func.c \
	  	plarser/tokenize.c \
	  	utils/utils_string.c \
	  	megashell.c \
		test_utils.c \
	  	main.c


HEADER_DIR = include
HEADERS = input.h \
		  plarser.h \
		  megashell.h
OBJ_DIR = obj



SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))


OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJ_DIRS := $(dir $(OBJS))

.PHONY: make_libs

all: make_libs argv_test $(NAME)

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

argv_test: tests/argv_test.c
	gcc tests/argv_test.c -o argv_test
