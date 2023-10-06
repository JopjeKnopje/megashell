/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/06 19:41:43 by ivan-mel         ###   ########.fr       */
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
