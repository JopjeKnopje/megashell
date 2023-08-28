/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:00:42 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/28 16:30:06 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
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

bool	builtin_run_unset(t_exec *execute, t_cmd_list *cmds);
bool	builtin_run_pwd(t_exec *execute, t_cmd_list *cmds);
bool	builtin_run_env(t_exec *execute, t_cmd_list *cmds);
bool	builtin_run_echo(t_exec *execute, t_cmd_list *cmds);
bool	builtin_run_cd(t_exec *execute, t_cmd_list *cmdsd);
bool	builtin_run_export(t_exec *execute, t_cmd_list *cmdsd);
bool	builtin_run_exit(t_exec *execute, t_cmd_list *cmds);
bool	add_to_env(t_exec *execute, t_cmd_list *cmds, char *cmd_start);
void	print_environment(char **envp);
char 	**allocate_and_copy_envp(char **envp, int count, t_cmd_list *cmds, char *cmd_start);
bool	builtin_run_export(t_exec *execute, t_cmd_list *cmds);
bool	update_existing_variable(t_exec *execute, t_cmd_list *cmds, char *cmd_start);

#endif
