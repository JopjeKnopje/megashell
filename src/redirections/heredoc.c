/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 02:23:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "plarser.h"
#include "libft.h"

// char	*with_env()
// {
	
// }

// void *expand_line(char *line)
// {
// 	int		i;
// 	char	*new_line;
// 	char	*result;

// 	i = 0;
// 	new_line = NULL;
// 	result = NULL;
// 	while (line[i])
// 	{
// 		// if (line[i] == '$')
// 		// {
// 		// 	with_env();
// 		// }
// 		// else
// 		// {
// 			result = without_env(line, new_line, i);
// 		// }
// 		i++;
// 	}
// 	return (result);
// }

uint8_t	read_from_heredoc(char *close_line, int pipe_fd)
{
	char	*line;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, close_line, ft_strlen(close_line) + 1))
		{
			free(line);
			printf("same\n");;
			break ;
		}
		write(pipe_fd, line, strlen(line) + 1);
		write(pipe_fd, "\n", 1);
		free (line);
	}
	return (EXIT_SUCCESS);
}

bool	handle_heredoc(t_cmd_frame *f)
{
	int	pipe_fd[2];
	int	pid;
	int	status;
	uint8_t	child_exit_code;

	if (pipe(pipe_fd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		close (pipe_fd[PIPE_READ]);
		// TODO: In parser add serpate field for heredoc_delim and use that here instead of outfile.
		child_exit_code = read_from_heredoc(f->outfile, pipe_fd[PIPE_WRITE]);
		close (pipe_fd[PIPE_WRITE]);
		exit(child_exit_code);
	}
	close(pipe_fd[PIPE_WRITE]);
	// dup_stdin(pipe_fd[PIPE_READ]); // dit wordt nu geduped in childprocess, moet wss in parent
	// close(pipe_fd[PIPE_READ]);
	
	// run_builtin(builtin, meta, cmds);

	waitpid(pid, &status, 0);
	
	child_exit_code = WEXITSTATUS(status);
	dprintf(STDERR_FILENO, "child_exit %d\n", child_exit_code);
	return (child_exit_code == 0);
}
