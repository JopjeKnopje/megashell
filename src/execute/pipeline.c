/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipeline.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/05 02:54:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/17 15:09:11 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include "heredoc.h"
#include "execute.h"
#include <assert.h>
#include <unistd.h>


static bool	run_command(t_meta *meta, t_cmd_frame *cmd)
{
	t_builtin	is_builtin;
	char *cmd_in_path;

	is_builtin = get_builtin(cmd->argv[0]);
	if (is_builtin)
		return (run_builtin(is_builtin, meta, cmd));

	cmd_in_path = access_possible(meta, cmd->argv[0]);
	if (cmd_in_path)
	{
		if (execve(cmd_in_path, cmd->argv, meta->envp) == -1)
		{
			print_error(get_error_name(ERROR_ACCESS));
			return (false);
		}
		return (true);
	}
	return (false);
}

static int child_proc(t_meta *meta, t_cmd_list *cmds)
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
	redirections(&cmds->content);
	return (!run_command(meta, &cmds->content));
}

static bool pipeline_node(t_meta *meta, t_cmd_list *cmds, int *pid)
{
	if (cmds->next && pipe(cmds->pipe) == -1)
	{
		print_error(get_error_name(ERROR_PIPE));
		return (false);
	}
	*pid = fork();
	if (*pid == -1)
	{
		print_error(get_error_name(ERROR_FORK));
		return (false);
	}
	if (!*pid)
	{
		exit(child_proc(meta, cmds));
	}
	if (cmds->prev)
	{
		close(cmds->prev->pipe[PIPE_READ]);
		close(cmds->prev->pipe[PIPE_WRITE]);
	}
	return (true);
}

// TODO: maybe handle when the child segfaults n stuff.
static int pipeline_wait(int *pids, size_t proc_count)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < proc_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (!WIFEXITED(status))
		assert(0 && "Handle segfaults etc.\n");
	return (WEXITSTATUS(status));
}

bool	pipeline_start(t_meta *meta, t_cmd_list *cmds)
{
	size_t 	proc_count;
	pid_t 	*pids;
	int		i;
	int		last_exit;
	t_hd_list *heredoc_pipes;


	proc_count = pr_lst_count(cmds);
	pids = ft_calloc(proc_count, sizeof(int));
	if (!pids)
		return (false);

	// heredoc_pipes should be a linked list where we 'consume' the first element when redirecting the pipe[read] to our child proc.
	heredoc_pipes = run_heredocs(cmds);



	return true;



	i = 0;
	while (cmds)
	{
		if (!pipeline_node(meta, cmds, &pids[i]))
		{
			assert(1 && "pipeline_node failure\n");
		}
		cmds = cmds->next;
		i++;
	}
	last_exit = pipeline_wait(pids, proc_count);
	free(pids);
	printf("last exitcode: %d\n",(last_exit));
	return (true);
}
