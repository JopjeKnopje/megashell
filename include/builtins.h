/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:00:42 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:35:49 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
#include "megashell.h"
# include "plarser.h"

typedef struct s_exec t_exec;

typedef enum e_builtin {
	BUILTIN_INVALID,
	BUILTIN_PWD,
	BUILTIN_ENV,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_EXIT,
	BUILTIN_COUNT,
}	t_builtin;

static const char *BUILTINS_NAME[BUILTIN_COUNT] = {
	"INVALID",
	"pwd",
	"env",
	"echo",
	"cd",
	"export",
	"unset",
	"exit"};

bool	builtin_run_unset(t_meta *execute, t_cmd_list *cmds);
bool	builtin_run_pwd(t_meta *execute, t_cmd_list *cmds);
bool	builtin_run_env(t_meta *execute, t_cmd_list *cmds);
bool	builtin_run_echo(t_meta *execute, t_cmd_list *cmds);
bool	builtin_run_cd(t_meta *execute, t_cmd_list *cmdsd);
bool	builtin_run_exit(t_meta *meta, t_cmd_list *cmds);
bool	builtin_run_export(t_meta *execute, t_cmd_list *cmds);

bool	correct_input(char *content);
bool	add_to_env(char **envp, t_cmd_list *cmds, char *cmd_start);
void	print_environment(char **envp);
bool	handle_export_input_errors(char *cmd_start);
bool	handle_export_existing_variable(char **execute, char *cmd_start);
bool	handle_export_new_variable(char **meta, t_cmd_list *cmds, char *cmd_start);

#endif
