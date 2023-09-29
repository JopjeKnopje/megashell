/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/29 22:21:16 by ivan-mel         ###   ########.fr       */
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

void	child_heredoc(char *close_line, int pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, close_line, ft_strlen(close_line) + 1))
		{
			free(line);
			printf("same\n");
			close (pipe_fd);
			exit(0);
		}
		printf("diff\n");
		write(pipe_fd, line, strlen(line) + 1);
		write(pipe_fd, "\n", 1);
		free (line);
	}
	close (pipe_fd);
	exit(0);
}

void	handle_heredoc(t_cmd_frame *cmd_frame)
{
	int	pipe_fd[2];
	int	pid;
	int	status;

	if (pipe(pipe_fd) == -1)
	{
		print_error(get_error_name(ERROR_PIPE));
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		print_error(get_error_name(ERROR_FORK));
		return ;
	}
	if (pid == 0)
	{
		close (pipe_fd[PIPE_READ]);
		child_heredoc(cmd_frame->outfile, pipe_fd[PIPE_WRITE]);
	}
	else
	{
		close(pipe_fd[PIPE_WRITE]);
		waitpid(pid, &status, 0);
	}
}
