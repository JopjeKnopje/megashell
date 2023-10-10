/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:31 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/10 17:06:03 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "utils.h"

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

bool	run_argument(t_meta *meta, t_cmd_frame *cmd)
{
	int		path_len;
	char	*pwd_now;
	char	**prev_pwd;

	pwd_now = NULL;
	path_len = ft_strlen(cmd->argv[1]);
	prev_pwd = search_in_path(meta->envp, "OLDPWD=");
	if (ft_strncmp(cmd->argv[1], "-", 1) == 0 \
			&& path_len == 1)
	{
		if (set_oldpwd(meta, cmd->argv[1], prev_pwd) == false \
			|| set_pwd(meta, pwd_now) == false)
			return (false);
		return (true);
	}
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
		tmp_home = search_in_path(meta->envp, "HOME=");
		if (!tmp_home)
			return (false);
		chdir(tmp_home[0]);
		free_2d(tmp_home);
		getcwd(cwd, sizeof(cwd));
		return (true);
	}
	if (run_argument(meta, cmd) == false)
	{
		print_error(strerror(errno));
		return (false);
	}
	getcwd(cwd, sizeof(cwd));
	return (true);
}
