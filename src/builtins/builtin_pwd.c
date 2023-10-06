/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:52 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/06 18:06:54 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"

bool	builtin_run_pwd(t_meta *meta, t_cmd_frame *cmd)
{
	char	cwd[PATH_MAX];

	(void) meta;
	(void) cmd;
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
