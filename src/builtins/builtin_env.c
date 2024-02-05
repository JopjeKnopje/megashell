/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/19 14:59:29 by ivan-mel         ###   ########.fr       */
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
	{
		printf("Please use env without second argument!\n");
		return (0);
	}
	while (meta->envp && meta->envp[i])
	{
		printf("%s\n", meta->envp[i]);
		i++;
	}
	return (0);
}
