/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:52 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/14 17:58:38 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_pwd(t_exec *execute, t_cmd_list *cmds)
{
	(void) execute;
	(void)	cmds;
	char	cwd[PATH_MAX];/* PATH_MAX: limit for the lenght of file name */
	ft_bzero(&cwd, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (false);
	}
	return (true);
}
