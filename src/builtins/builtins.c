/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/02/04 22:27:56 by joppe         ########   odam.nl         */
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
#include <string.h>
#include <unistd.h>

typedef int	(*t_builtin_func)(t_meta *meta, t_cmd_frame *cmd);

const char	*get_builtin_name(int i)
{
	static const char	*builtin_names[BUILTIN_COUNT] = { 
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

	return (builtin_names[i]);
}

t_builtin_func	get_builtin_func(t_builtin builtin)
{
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

	return (funcs[builtin]);
}

t_builtin	get_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (BUILTIN_INVALID);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, get_builtin_name(i), \
		strlen_largest(get_builtin_name(i), cmd)) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_INVALID);
}

int	run_builtin(t_builtin builtin, t_meta *meta, t_cmd_frame *cmd)
{
	int			exit_status;
	int			fd;
	int			fds[2];

	fd = -1;
	if (cmd->heredoc_delim)
	{
		fd = handle_heredoc(meta, cmd, &exit_status);
		if (fd == -1)
			return (INTERNAL_FAILURE);
	}
	fds[PIPE_WRITE] = dup(STDOUT_FILENO);
	fds[PIPE_READ] = dup(STDIN_FILENO);
	if (!redirections(cmd, fd))
		return (print_error(strerror(errno)));
	exit_status = (get_builtin_func(builtin)(meta, cmd));
	if (!dup_stdin(fds[PIPE_READ]))
		print_error("error dup_stdin\n");
	if (!dup_stdout(fds[PIPE_WRITE]))
		print_error("error dup_stdout\n");
	return (exit_status);
}
