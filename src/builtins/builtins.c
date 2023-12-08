/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/08 17:45:30 by jboeve        ########   odam.nl         */
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

static t_builtin_func get_builtin_func(t_builtin builtin)
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
	return funcs[builtin];
}


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
	t_hd_list *head = NULL;
	int	exit_status;
	int fds[2];
	int heredoc_fd;

	if (cmd->heredoc_delim)
	{
		heredoc_fd = handle_heredoc(cmd, &exit_status);
		if (heredoc_fd == INTERNAL_FAILURE)
		{
			return (INTERNAL_FAILURE);
		}
		head = append_heredoc(&head, heredoc_fd);
		if (!head)
			return (INTERNAL_FAILURE);
	}
	fds[PIPE_WRITE] = dup(STDOUT_FILENO);
	if (fds[PIPE_WRITE] == INTERNAL_FAILURE)
	{
		hd_lst_free(head);
		close(heredoc_fd);
		return (INTERNAL_FAILURE);
	}
	fds[PIPE_READ] = dup(STDIN_FILENO);
	if (fds[PIPE_READ] == INTERNAL_FAILURE)
	{
		hd_lst_free(head);
		close(heredoc_fd);
		close(fds[PIPE_WRITE]);
		return (INTERNAL_FAILURE);
	}
	if (!redirections(cmd, &head))
	{
		hd_lst_free(head);
		close(fds[PIPE_WRITE]);
		close(fds[PIPE_READ]);
		print_error(strerror(errno));
		return (INTERNAL_FAILURE);
	}

	exit_status = (*get_builtin_func(builtin))(meta, cmd);

	if (!dup_stdin(fds[PIPE_READ]))
		return ((print_error(get_error_name(ERROR_DUP2)) * 0) - 1);
	if (!dup_stdin(fds[PIPE_WRITE]))
		return ((print_error(get_error_name(ERROR_DUP2)) * 0) - 1);
	return (exit_status);
}
