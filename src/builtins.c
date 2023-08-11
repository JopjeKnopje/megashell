/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/11 16:57:22 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	is_it_builtin(char *cmd)
{
	// if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd)) == 0)
	// 	echo_builtin(cmd);
	// else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd)) == 0)
	// 	cd_builtin();
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		pwd_builtin();
	// else if (ft_strncmp(cmd[0], "export", ft_strlen(cmd)) == 0)
	// 	export_builtin();
	// else if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd)) == 0)
	// 	unset_builtin();
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		env_builtin();
	// else if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd)) == 0)
	// 	exit_builtin();
}
