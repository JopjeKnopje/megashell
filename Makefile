# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                          :+:    :+:              #
#                                                     +:+ +:+         +:+      #
#    By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 13:32:22 by jboeve            #+#    #+#              #
#    Updated: 2023/10/05 04:14:28 by joppe         ########   odam.nl          #
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

SRCS =  execute/error.c \
		execute/path.c \
		execute/free.c \
		execute/environment.c \
		execute/execute.c \
		execute/execute_utils.c \
		execute/pipeline.c \
		builtins/builtins.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_export_utils.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		execute/access.c \
		execute/access_utils.c \
		input/prompt.c \
	  	input/signals.c \
	  	input/history_file.c \
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
		redirections/redirections.c \
		redirections/heredoc.c \
		test_utils.c \
	  	megashell.c \
		main.c \

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

all: make_libs $(NAME)

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
