/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                      :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 15:16:52 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

// If no directory operand is given and the HOME environment variable is set
// to a non-empty value, the cd utility shall behave as if the directory named
// in the HOME environment variable was specified as the directory operand.

char	**print_home_env(char **envp)
{
	int		i;
	int		dup_home_index;
	int		envp_len;
	char	**dup_home;

	i = 0;
	dup_home_index = 0;
	envp_len = ft_strlen(envp[i]);
	dup_home = (char **)malloc(sizeof(char *) * (envp_len + 1));
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], "HOME=", 5) == 0))
		{
			dup_home[dup_home_index] = ft_strdup(envp[i] + 5);
			dup_home_index++;
		}
		i++;
	}
	dup_home[dup_home_index] = NULL;
	return (dup_home);
}

bool	builtin_run_cd(t_meta *meta, t_cmd_frame *cmd)
{
	char		cwd[PATH_MAX];
	char		**tmp_home;
	int			path_len;

	if (!cmd->argv[1])
	{
		tmp_home = print_home_env(meta->envp);
		if (!tmp_home)
		{
			return (false);
		}
		chdir(tmp_home[0]);
		free_2d(tmp_home);
		getcwd(cwd, sizeof(cwd));
		// printf("Current working dir: %s\n", cwd);
		return (true);
	}
	path_len = ft_strlen(cmd->argv[1]);
	if (strncmp(cmd->argv[1], "..", path_len) == 0 || strncmp(cmd->argv[1], "../", path_len) == 0)
	{
		chdir("../");
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->argv[1]);
		return false;
	}
	getcwd(cwd, sizeof(cwd));
	// printf("Current working dir: %s\n", cwd);
	return (true);
}
