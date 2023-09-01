/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:26:31 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_env(t_meta *meta, t_cmd_list *cmds)
{
	int	i;

	i = 0;
	while (meta->envp[i])
	{
		printf("%s\n", meta->envp[i]);
		i++;
	}
	return (true);
}
