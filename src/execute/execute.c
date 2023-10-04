/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 16:28:01 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "plarser.h"
#include "redirections.h"
#include "execute.h"
#include "megashell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>

bool try_builtin(t_cmd_frame *cmd, t_meta *meta)
{
	t_builtin	is_builtin;
	is_builtin = get_builtin(cmd->argv[0]);
	if (is_builtin)
	{
		fprintf(stderr, "runing buitlin\n");
		run_builtin(is_builtin, meta, cmd);
		return  true;
	}
	return (false);
}

bool	run_command(t_meta *meta, t_cmd_frame *cmd)
{
	char *cmd_in_path;

	if (!cmd->argv)
		return false;

	if (try_builtin(cmd, meta))
		return true;

	cmd_in_path = access_possible(meta, cmd->argv[0]);
	if (cmd_in_path)
	{
		execve(cmd_in_path, cmd->argv, meta->envp);
		print_error(get_error_name(ERROR_ACCESS));
		return false;
	}
	return true;
}


int fork_wrap()
{
	static int count = 0;
	count++;
	printf("forked %d times\n", count);
	return fork();
}


int cmd_count(t_cmd_list *cmds)
{
	int count = 0;
	while (cmds)
	{
		cmds = cmds->next;
		count++;
	}
	return count;
}

bool	start_pipeline(t_meta *meta, t_cmd_list *cmds)
{
	int		status;
	int 	count_cmds = cmd_count(cmds);
	int		*pids = ft_calloc(sizeof(int), count_cmds);
	int i = 0;
	if (!pids)
		return false;

	while (cmds)
	{
		if (cmds->next && pipe(cmds->pipe) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return (false);
		}
		pids[i] = fork_wrap();
		if (pids[i] == -1) /* fork returns -1 in case of error */
		{
			print_error(get_error_name(ERROR_FORK));
			return (false);
		}
		if (pids[i] == 0) /* fork returns 0 for child process */
		{
			if (cmds->prev)
			{
				if (dup2(cmds->prev->pipe[PIPE_READ], STDIN_FILENO) == -1)
					perror(strerror(errno));
				close(cmds->prev->pipe[PIPE_READ]);
				close(cmds->prev->pipe[PIPE_WRITE]);
			}
			if (cmds->next)
			{
				close(cmds->pipe[PIPE_READ]);
				if (dup2(cmds->pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
					perror(strerror(errno));
				close(cmds->pipe[PIPE_WRITE]);
			}
			// setup_io(cmds);
			if (run_command(meta, &cmds->content))
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		if (cmds->prev)
		{
			close(cmds->prev->pipe[PIPE_READ]);
			close(cmds->prev->pipe[PIPE_WRITE]);
		}
		if (!cmds->next)
		{
			close(cmds->pipe[PIPE_READ]);
			close(cmds->pipe[PIPE_WRITE]);
		}
		cmds = cmds->next;
		i++;
	}

	i = 0;
	while (i < count_cmds)
	{
		waitpid(pids[i], &status, 0);
		printf("%d exitcode: %d\n", i, WEXITSTATUS(status));
		i++;
	}
	return (true);
}

bool	execute(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;

	if (cmds->next)
		return (start_pipeline(meta, cmds));

	else if (cmds->content.argv)
		is_builtin = get_builtin(cmds->content.argv[0]);
	else 
		is_builtin = BUILTIN_INVALID;
	if (is_builtin)
		return run_builtin(is_builtin, meta, &cmds->content);
	return false;
}
