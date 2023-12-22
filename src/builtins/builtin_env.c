/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/22 23:36:51 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"

int	builtin_run_env(t_meta *meta, t_cmd_frame *cmd)
{
	int	i;

	(void) cmd;
	i = 0;
	if (cmd->argv[1])
		return (0);
	while (meta->envp && meta->envp[i])
	{
		printf("%s\n", meta->envp[i]);
		i++;
	}
	return (0);
}
