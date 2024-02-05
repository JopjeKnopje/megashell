/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:33:28 by jboeve            #+#    #+#             */
/*   Updated: 2024/02/05 15:23:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	return (megashell(envp));
	return 0;
}
