# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                          :+:    :+:              #
#                                                     +:+ +:+         +:+      #
#    By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 13:32:22 by jboeve            #+#    #+#              #
#    Updated: 2023/08/28 18:29:54 by joppe         ########   odam.nl          #
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

SRCS = main.c \
		error.c \
		path.c \
		free.c \
		environment.c \
		execute.c \
		execute_utils.c \
		builtins/builtins.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		utils.c \
		access.c \
		input/prompt.c \
	  	input/signals.c \
	  	input/history_file.c \
	  	input/aliases.c \
	  	plarser/lexer.c \
	  	plarser/lexer_list.c \
	  	plarser/lexer_utils.c \
	  	plarser/plarser.c \
	  	plarser/syntax.c \
	  	plarser/syntax_func.c \
	  	plarser/tokenize.c \
	  	plarser/parser.c \
	  	plarser/parser_list.c \
	  	utils/utils_string.c \
	  	megashell.c \
		test_utils.c \

HEADER_DIR = include
HEADERS = input.h \
		  plarser.h \
		  megashell.h \
		  builtins.h \
		  execute.h \
		  test_utils.h \
		  utils.h

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
