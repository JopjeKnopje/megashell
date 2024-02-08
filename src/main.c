/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:33:28 by jboeve            #+#    #+#             */
/*   Updated: 2024/02/07 13:34:47 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	return (megashell(envp));
}
