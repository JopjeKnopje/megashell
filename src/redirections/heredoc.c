/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:06:19 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/15 19:44:13 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "execute.h"
#include "plarser.h"
#include "libft.h"

char	*without_env(char *line1, char *line2, int i)
{
	char	*joined_line;
	char	*new_line;

	while (line1[i])
		i++;
	new_line = malloc(sizeof(char ) * i);
	if (!joined_line)
		return (NULL);
	joined_line = ft_strjoin(line2, line1);
	if (!joined_line)
		return (NULL);
	free(line1);
	free(line2);
	return (joined_line);
}

// char	*with_env()
// {
	
// }

void *expand_line(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line[i])
	{
		// if (line[i] == '$')
		// {
		// 	with_env();
		// }
		// else
		// {
			without_env(line, new_line, i);
		// }
		i++;
	}
}

void	child_heredoc(char *close_line, int pipe_fd)
{
	char	*line_read;
	char	*expanded_line;

	printf("hey\n");
	while (1)
	{
		line_read = readline("> ");
		if (!line_read)
			break ;
		if (ft_strncmp(close_line, line_read, ft_strlen(line_read)) == 1)
		{
			free(line_read);
			break ;
		}
		expanded_line = expand_line(line_read);
		write(pipe_fd, expanded_line, strlen(expanded_line) + 1);
		write(pipe_fd, "\n", 1);
		free (expanded_line);
		free (line_read);
	}
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
		close (pipe_fd[IN_READ]);
		child_heredoc(cmd_frame->outfile, pipe_fd[OUT_WRITE]);
	}
	else
	{
		close(pipe_fd[OUT_WRITE]);
		waitpid(pid, &status, 0);
	}
}
