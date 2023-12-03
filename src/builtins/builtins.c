/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/03 01:08:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"
#include "heredoc.h"
#include "megashell.h"
#include "plarser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int	(*t_builtin_func)(t_meta *meta, t_cmd_frame *cmd);

static const char *BUILTINS_NAME[BUILTIN_COUNT] = {
	"INVALID",
	"pwd",
	"env",
	"echo",
	"cd",
	"export",
	"unset",
	"exit",
	"history",
};

t_builtin	get_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (BUILTIN_INVALID);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, BUILTINS_NAME[i], \
		strlen_largest(BUILTINS_NAME[i], cmd)) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_INVALID);
}

int	run_builtin(t_builtin builtin, t_meta *meta, t_cmd_frame *cmd)
{
	int	exit_status;
	const t_builtin_func	funcs[] = {
		NULL, \
		builtin_run_pwd, \
		builtin_run_env, \
		builtin_run_echo, \
		builtin_run_cd, \
		builtin_run_export, \
		builtin_run_unset, \
		builtin_run_exit, \
		builtin_run_history, \
	};


	t_hd_list *head = NULL;
	if (cmd->heredoc_delim)
	{
		int fd = handle_heredoc(cmd, &exit_status);
		if (fd == -1)
			UNIMPLEMENTED("return malloc failure signal as exit code?\n");
		head = append_heredoc(&head, fd);
	}

	int fd_out = dup(STDOUT_FILENO);
	int fd_in = dup(STDIN_FILENO);
	redirections(cmd, &head);

	exit_status = (*funcs[builtin])(meta, cmd);

	if (!dup_stdin(fd_in))
	{
		fprintf(stderr, "error dup_stdin\n");
	}
	if (!dup_stdout(fd_out))
	{
		fprintf(stderr, "error dup_stdout\n");
	}
	return (exit_status);
}
