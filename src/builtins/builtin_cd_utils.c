/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:09:14 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/11/06 23:27:39 by joppe         ########   odam.nl         */
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
	arg = ft_strdup(pwd);
	if (!prepare_variable(arg))
		return (false);
	if (exists_in_env(meta->envp, pwd, arg, ft_strlen(arg)) == false)
		return (false);
	handle_export_oldpwd_variable(meta->envp, cur_pwd);
	free(arg);
	return (true);
}
