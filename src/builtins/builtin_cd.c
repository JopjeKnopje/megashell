/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/06 15:39:28 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

// If no directory operand is given and the HOME environment variable is set
// to a non-empty value, the cd utility shall behave as if the directory named
// in the HOME environment variable was specified as the directory operand.

char	**search_for_pwd(char **envp)
{
	int		i;
	int		dup_pwd_index;
	int		envp_len;
	char	**dup_pwd;

	i = 0;
	dup_pwd_index = 0;
	envp_len = ft_strlen(envp[i]);
	dup_pwd = (char **)malloc(sizeof(char *) * (envp_len + 1));
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], "OLDPWD=", 7) == 0))
		{
			dup_pwd[dup_pwd_index] = ft_strdup(envp[i] + 7);
			dup_pwd_index++;
		}
		i++;
	}
	dup_pwd[dup_pwd_index] = NULL;
	return (dup_pwd);
}

bool	set_oldpwd(t_meta *meta, char *cmd, char **prev_pwd)
{
	char	cwd[PATH_MAX];
	char	*pwd_now;
	char	*cur_pwd;
	char	*new_pwd;
	char	*arg;

	cur_pwd = strdup(getcwd(cwd, sizeof(cwd)));
	new_pwd = cur_pwd;
	if (ft_strncmp(cmd, "-", 1) == 0)
		chdir(*prev_pwd);
	else
		if (chdir(cmd) == -1)
			return (false);
	pwd_now = getcwd(cwd, sizeof(cwd));
	new_pwd = change_oldpwd(pwd_now, cur_pwd);
	arg = ft_strdup(new_pwd);
	if (set_pwd(meta, pwd_now) == false || !prepare_variable(arg) \
		|| exists_in_env(meta->envp, new_pwd, arg, ft_strlen(arg)) == false)
		return (false);
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	if (ft_strncmp(cmd, "-", 1) == 0)
		printf("%s\n", pwd_now);
	free(arg);
	free_2d(prev_pwd);
	return (true);
}

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

bool	run_argument(t_meta *meta, t_cmd_frame *cmd)
{
	int		path_len;
	char	*pwd_now;
	char	**prev_pwd;

	pwd_now = NULL;
	path_len = ft_strlen(cmd->argv[1]);
	prev_pwd = search_for_pwd(meta->envp);
	if (access(cmd->argv[1], F_OK) != 0)
	{
		if (ft_strncmp(cmd->argv[1], "-", 1) == 0 \
			&& path_len == 1)
		{
			if (set_oldpwd(meta, cmd->argv[1], prev_pwd) == false \
			|| set_pwd(meta, pwd_now) == false)
				return (false);
			return (true);
		}
		return (false);
	}
	if (strncmp (cmd->argv[1], ".", 1) == 0 && ft_strlen(cmd->argv[1]) == 1)
		return (true);
	if (set_oldpwd(meta, cmd->argv[1], prev_pwd) == false \
		|| set_pwd(meta, pwd_now) == false)
		return (false);
	return (true);
}

bool	builtin_run_cd(t_meta *meta, t_cmd_frame *cmd)
{
	char		cwd[PATH_MAX];
	char		**tmp_home;

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
		return (true);
	}
	if (run_argument(meta, cmd) == false)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->argv[1]);
		return (false);
	}
	getcwd(cwd, sizeof(cwd));
	return (true);
}
