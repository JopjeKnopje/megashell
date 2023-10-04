/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 23:00:08 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"

bool	builtin_run_env(t_meta *meta, t_cmd_frame *cmd)
{
	int	i;

	(void) cmd;

	i = 0;
	while (meta->envp[i])
	{
		printf("%s\n", meta->envp[i]);
		i++;
	}
	return (true);
}
