/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/05 11:43:48 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

// If no directory operand is given and the HOME environment variable is set
// to a non-empty value, the cd utility shall behave as if the directory named
// in the HOME environment variable was specified as the directory operand.

bool	handle_export_oldpwd_variable(char **envp, char *cmd_start)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (cmd_start)
		free(cmd_start);
	return (true);
}

char	*change_oldpwd(char *dir, char *cur_pwd)
{
	char	*old_pwd;
	char	*path;
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = NULL;
	if (!dir)
		return (NULL);
	old_pwd = "OLDPWD=";
	path = ft_strdup(dir);
	if (!path)
		return (NULL);
	new_pwd = ft_strjoin(old_pwd, cur_pwd);
	if (!new_pwd)
		return (NULL);
	return (new_pwd);
	
}

char	*change_pwd(char *dir, char *cur_pwd)
{
	char	*old_pwd;
	char	*path;
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = NULL;
	if (!dir)
		return (NULL);
	old_pwd = "PWD=";
	path = ft_strdup(dir);
	if (!path)
		return (NULL);
	new_pwd = ft_strjoin(old_pwd, cur_pwd);
	if (!new_pwd)
		return (NULL);
	return (new_pwd);
	
}

bool	set_pwd(t_meta *meta, char *pwd_now)
{
	char	cwd[PATH_MAX];
	char *pwd;
	char *arg;
	char	 *cur_pwd;
	char	 *new_pwd;

	cur_pwd = strdup(getcwd(cwd, sizeof(cwd)));
	new_pwd = cur_pwd;
	pwd_now = getcwd(cwd, sizeof(cwd));
	pwd = change_pwd(pwd_now, cur_pwd);
	arg = ft_strdup(pwd);
	if (!prepare_variable(arg))
		return (false);
	if (exists_in_env(meta->envp, pwd, arg, ft_strlen(arg)) == false)
			return(false);
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	free(arg);
	return (true);
}

bool	set_oldpwd(t_meta *meta, char *dash)
{
	char	cwd[PATH_MAX];
	char	*pwd_now;
	char	 *cur_pwd;
	char	 *new_pwd;
	char	 *arg;

	cur_pwd = strdup(getcwd(cwd, sizeof(cwd)));
	new_pwd = cur_pwd;
	chdir("..");
	pwd_now = getcwd(cwd, sizeof(cwd));
	new_pwd = change_oldpwd(pwd_now, cur_pwd);
	if (set_pwd(meta, pwd_now) == false)
		return(false);
	arg = ft_strdup(new_pwd);
	if (!prepare_variable(arg))
		return (false);
	if (exists_in_env(meta->envp, new_pwd, arg, ft_strlen(arg)) == false)
		return(false);
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	if (ft_strncmp(dash, "-", 1) == 0)
		printf("%s\n", pwd_now);
	free(arg);
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

bool	builtin_run_cd(t_meta *meta, t_cmd_frame *cmd)
{
	char		cwd[PATH_MAX];
	char		**tmp_home;
	int			path_len;
	char		*pwd_now;

	pwd_now = NULL;
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
	if (strncmp(cmd->argv[1], "-", 1) == 0)
	{
		if (set_oldpwd(meta, cmd->argv[1]) == false)
			return(false);
		return(true);
	}
	path_len = ft_strlen(cmd->argv[1]);
	if (strncmp(cmd->argv[1], "..", path_len) == 0 || strncmp(cmd->argv[1], "../", path_len) == 0)
	{
		if (set_oldpwd(meta, cmd->argv[1]) == false)
			return(false);
		if (set_pwd(meta, pwd_now) == false)
			return(false);
		return (true);
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->argv[1]);
		return false;
	}
	getcwd(cwd, sizeof(cwd));
	return (true);
}
