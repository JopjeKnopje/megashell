/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:43:52 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 16:23:46 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include "utils.h"

int	builtin_run_pwd(t_meta *meta, t_cmd_frame *cmd)
{
	char	cwd[PATH_MAX];

	(void) cmd;
	(void) meta;
	ft_bzero(&cwd, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		return (-1);
	return (0);
}
