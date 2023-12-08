/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                      :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/08 13:25:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "utils.h"
#include <stdio.h>

bool	set_pwds(t_meta *meta, char *pwd_now, char *cur_pwd)
{
	char	*arg;
	char	*new_pwd;

	new_pwd = change_oldpwd(pwd_now, cur_pwd);
	arg = ft_strdup(new_pwd);
	if (set_pwd(meta, pwd_now) == false || !prepare_variable(arg) \
		|| exists_in_env(meta->envp, new_pwd, arg, ft_strlen(arg)) == false)
	{
		free(arg);
		free(new_pwd);
		return (false);
	}
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	free(arg);
	free(new_pwd);
	return (true);
}

bool	set_oldpwd(t_meta *meta, char *cmd, char **prev_pwd)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*pwd_now;
	char	*cur_pwd;

	tmp = getcwd(cwd, sizeof(cwd));
	if (!tmp)
	{
		if (chdir(cmd) == -1)
			return (false);
		return (true);
	}
	cur_pwd = ft_strdup(tmp);
	if (ft_strncmp(cmd, "-", 1) == 0)
		chdir(*prev_pwd);
	else
		if (chdir(cmd) == -1)
		{
			free(cur_pwd);
			return (false);
		}
	pwd_now = getcwd(cwd, sizeof(cwd));
	if (set_pwds(meta, pwd_now, cur_pwd) == false)
	{
		free(cur_pwd);
		return (false);
	}
	if (ft_strncmp(cmd, "-", 1) == 0)
		printf("%s\n", pwd_now);
	return (true);
}

bool	run_argument(t_meta *meta, t_cmd_frame *cmd)
{
	int		path_len;
	char	*pwd_now;
	char	**prev_pwd;

	pwd_now = NULL;
	path_len = ft_strlen(cmd->argv[1]);
	prev_pwd = search_in_path(meta->envp, "OLDPWD=");
	if (!prev_pwd)
		return (false);
	if (ft_strncmp(cmd->argv[1], "-", 1) == 0 \
			&& path_len == 1)
	{
		if (set_oldpwd(meta, cmd->argv[1], prev_pwd) == false \
			|| set_pwd(meta, pwd_now) == false)
		{
			free_2d(prev_pwd);
			return (false);
		}
		free_2d(prev_pwd);
		return (true);
	}
	bool oldpwd = set_oldpwd(meta, cmd->argv[1], prev_pwd);
	bool pwd = set_pwd(meta, pwd_now);
	if (!oldpwd || !pwd)
	{
		printf("oldpwd [%s] pwd [%s]\n", oldpwd ? "TRUE" : "FALSE", pwd ? "TRUE" : "FALSE");
		free_2d(prev_pwd);
		printf("yup\n");
		return (false);
	}
	free_2d(prev_pwd);
	return (true);
}

int	builtin_run_cd(t_meta *meta, t_cmd_frame *cmd)
{
	char		cwd[PATH_MAX];
	char		**tmp_home;
	const size_t cmd_len = ft_strlen_2d(cmd->argv);

	if (cmd_len > 2)	
	{
		print_error(get_error_name(ERROR_ARGUMENTS));
		return (1);
	}
	if (!cmd->argv[1])
	{
		tmp_home = search_in_path(meta->envp, "HOME=");
		if (!tmp_home)
			return (0);
		chdir(tmp_home[0]);
		free_2d(tmp_home);
		getcwd(cwd, sizeof(cwd));
		return (0);
	}
	if (run_argument(meta, cmd) == false)
	{
		print_error(strerror(errno));
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	return (0);
}
