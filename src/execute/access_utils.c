/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:11:57 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:46:42 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*find_executable_in_path(char **split_path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
