/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:00:42 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/06 17:35:33 by ivan-mel         ###   ########.fr       */
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
	"exit",
};

bool	builtin_run_unset(t_meta *meta, t_cmd_frame *cmd);
bool	builtin_run_pwd(t_meta *meta, t_cmd_frame *cmd);
bool	builtin_run_env(t_meta *meta, t_cmd_frame *cmd);
bool	builtin_run_echo(t_meta *meta, t_cmd_frame *cmd);
bool	builtin_run_cd(t_meta *execute, t_cmd_frame *cmd);
bool	builtin_run_exit(t_meta *meta, t_cmd_frame *cmd);
bool	builtin_run_export(t_meta *execute, t_cmd_frame *cmd);

bool	correct_input(char *content);
char	**add_to_env(char **envp, char *arg, char *cmd_start);
void	print_environment(char **envp);
bool	prepare_variable(char *cmd_start);
bool	exists_in_env(char **envp, char *arg, char *variable, int len_var);
bool	handle_export_input_errors(char *cmd_start);
bool	handle_export_existing_variable(char **execute, char *cmd_start);
bool	handle_export_new_variable(t_meta *meta, char *arg, char *cmd_start);
char	*change_oldpwd(char *dir, char *cur_pwd);
char	*change_pwd(char *dir, char *cur_pw);
bool	handle_export_oldpwd_variable(char **envp, char *cmd_start);
bool	set_pwd(t_meta *meta, char *pwd_now);

// builtins:
t_builtin	get_builtin(char *cmd);
bool		run_builtin(t_builtin builtin, t_meta *meta, t_cmd_frame *cmd);


#endif
