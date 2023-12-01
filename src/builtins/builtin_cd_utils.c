/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:09:14 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/01 17:58:49 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

char	*change_oldpwd(char *dir, char *cur_pwd)
{
	char	*old_pwd;
	char	*path;
	char	*new_pwd;

	new_pwd = NULL;
	if (!dir)
		return (NULL);
	old_pwd = ft_strdup("OLDPWD=");
	if (!old_pwd)
		return (NULL);
	path = ft_strdup(dir);
	if (!path)
	{
		free(old_pwd);
		return (NULL);
	}
	new_pwd = ft_strjoin(old_pwd, cur_pwd);
	if (!new_pwd)
	{
		free(path);
		free(old_pwd);
		return (NULL);
	}
	free(path);
	free(old_pwd);
	return (new_pwd);
}

char	*change_pwd(char *dir, char *cur_pwd)
{
	char	*old_pwd;
	char	*path;
	char	*new_pwd;

	if (!dir || !cur_pwd)
		return (NULL);
	new_pwd = NULL;
	old_pwd = ft_strdup("PWD=");
	if (!old_pwd)
		return (NULL);
	path = ft_strdup(dir);
	if (!path)
	{
		free(old_pwd);
		return (NULL);
	}
	new_pwd = ft_strjoin(old_pwd, cur_pwd);
	if (!new_pwd)
	{
		free(path);
		free(old_pwd);
		return (NULL);
	}
	free(path);
	free(old_pwd);
	return (new_pwd);
}

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

bool	set_pwd(t_meta *meta, char *pwd_now)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	char	*arg;
	char	*cur_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (false);
	cur_pwd = ft_strdup(cwd);
	if (!cur_pwd)
		return (false);
	pwd_now = getcwd(cwd, sizeof(cwd));
	pwd = change_pwd(pwd_now, cur_pwd);
	if (!pwd)
	{
		free(cur_pwd);
		return (false);
	}
	arg = pwd;
	if (!arg)
		return (false);
	if (!prepare_variable(arg) || exists_in_env(meta->envp, \
		pwd, arg, ft_strlen(arg)) == false)
	{
		free(arg);
		free(cur_pwd);
		return (false);
	}
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	free(arg);
	return (true);
}
