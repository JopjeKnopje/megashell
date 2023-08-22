
int	check_input(t_exec *execute, int pipes_fd[2], int prev_pipe, t_cmds *cmds)
{
	int		fd_in;
	t_cmds	*content;

	content = cmds->argv;
	if (cmds->prev == 0) /* first child */
	{
		close(pipes_fd[READ]);
		fd_in = open(execute->infile, O_RDONLY); /* infile is stdin */
		if (fd_in == -1)
			return (print_error(strerror(errno)));
		close(fd_in);
	}
	else /* redirect prev pipe to stdin */
		dup_stdin(prev_pipe);
	return (0);
}

int	check_output(t_exec *execute, int pipes_fd[2], int prev_pipe)
{
	int	fd_out;
	if (pipes_fd[WRITE] == STDOUT_FILENO) /* last child */
	{
		close(pipes_fd[WRITE]);
		fd_out = open(execute->argv[execute->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			return (print_error(strerror(errno)));
		dup_stdout(fd_out);
		close(fd_out);
	}
	else if (pipes_fd[WRITE] != STDOUT_FILENO) /* not sure about this check tomorrow */
	{
		dup_stdout(pipes_fd[WRITE]);
	}
	return (0);
}
