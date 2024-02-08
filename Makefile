# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                          :+:    :+:              #
#                                                     +:+ +:+         +:+      #
#    By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 13:32:22 by jboeve            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/02/08 22:50:32 by joppe         ########   odam.nl          #
=======
#    Updated: 2024/02/07 12:27:33 by jboeve        ########   odam.nl          #
>>>>>>> 8d31f5c99f663e190c98975a28a7ecd1851b898d
#                                                                              #
# **************************************************************************** #


######################
# OS Dependend flags #
######################
UNAME_S		:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
	I_RL	:= -I $(shell brew --prefix readline)/include
	L_RL	:= -L $(shell brew --prefix readline)/lib
endif

NAME		:= minishell
RUN_CMD		:= ./$(NAME)

CFLAGS		+= -Wall -Wextra -Werror
# CFLAGS		+= -Wall -Wextra 
CFLAGS		+= -g -fsanitize=address
# CFLAGS		+= -g



LIBFT		:=	libft/build/libft.a

IFLAGS		:= -Ilibft/include -Iinclude $(I_RL)
LFLAGS		:= -lreadline $(L_RL)
 
SRC_DIR		:=	src

SRCS		:= 	execute/error.c \
				execute/path.c \
				execute/free.c \
				execute/environment.c \
				execute/execute.c \
				execute/execute_utils.c \
				execute/pipeline_utils.c \
				execute/pipeline.c \
				execute/access.c \
				execute/heredoc_list.c \
				builtins/builtins.c \
				builtins/builtin_cd.c \
				builtins/builtin_cd_utils.c \
				builtins/builtin_echo.c \
				builtins/builtin_env.c \
				builtins/builtin_exit.c \
				builtins/builtin_export.c \
				builtins/builtin_export_utils.c \
				builtins/builtin_pwd.c \
				builtins/builtin_unset.c \
				builtins/builtin_history.c \
				input/prompt.c \
			  	input/signals.c \
			  	input/history_file.c \
			  	plarser/lexer.c \
			  	plarser/lexer_list.c \
			  	plarser/lexer_utils.c \
				plarser/lexer_utils2.c \
			  	plarser/plarser.c \
			  	plarser/syntax.c \
			  	plarser/syntax_func.c \
			  	plarser/syntax_func2.c \
			  	plarser/tokenize.c \
			  	plarser/parser.c \
			  	plarser/parser_utils.c \
			  	plarser/parser_joiner.c \
			  	plarser/parser_list.c \
			  	plarser/expander.c \
			  	plarser/expander_utils.c \
			  	plarser/expander_utils2.c \
			  	plarser/space_count.c \
			  	plarser/heredoc_expander.c \
			  	utils/utils_string.c \
				utils/utils_path.c \
				redirections/redirections.c \
				redirections/heredoc.c \
			  	megashell.c

HEADER_DIR	:=	include
HEADERS 	:=	input.h \
		 	 	plarser.h \
		 		megashell.h \
		 		builtins.h \
		 		execute.h \
		 		utils.h

OBJ_DIR		:=	obj

SRCS 		:=	$(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS 	:=	$(addprefix $(HEADER_DIR)/, $(HEADERS))


OBJS 		:=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJ_DIRS 	:=	$(dir $(OBJS))

.PHONY: make_libs

all: make_libs $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(SRC_DIR)/main.c
	$(CC) $(SRC_DIR)/main.c $(OBJS) $(LIBFT) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $< 

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
