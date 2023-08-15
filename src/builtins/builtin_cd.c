/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/15 18:14:54 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// If no directory operand is given and the HOME environment variable is set
// to a non-empty value, the cd utility shall behave as if the directory named
// in the HOME environment variable was specified as the directory operand.

char	**print_home_env(t_exec *execute)
{
	int		i;
	int		dup_home_index;
	int		envp_len;
	char	**dup_home;

	i = 0;
	dup_home_index = 0;
	envp_len = ft_strlen(execute->envp[i]);
	dup_home = (char **)malloc(sizeof(char *) * (envp_len + 1));
	while (execute->envp[i])
	{
		if ((ft_strncmp(execute->envp[i], "HOME=", 5) == 0))
		{
			dup_home[dup_home_index] = ft_strdup(execute->envp[i] + 5);
			dup_home_index++;
		}
		i++;
	}
	dup_home[dup_home_index] = NULL;
	return (dup_home);
}

bool	builtin_run_cd(t_exec *execute, t_cmd_list *cmds)
{
	char		cwd[PATH_MAX];
	char		**tmp_home;
	int			path_len;

	if (!cmds->action[1])
	{
		tmp_home = print_home_env(execute);
		if (!tmp_home)
			return (false);
		chdir(tmp_home[0]);
		getcwd(cwd, sizeof(cwd));
		printf("Current working dir: %s\n", cwd);
	}
	path_len = ft_strlen(cmds->action[1]);
	if (strncmp(cmds->action[1], "..", path_len) == 0
		|| strncmp(cmds->action[1], "../", path_len) == 0)
		chdir("../");
	getcwd(cwd, sizeof(cwd));
	printf("Current working dir: %s\n", cwd);
	return (true);
}
