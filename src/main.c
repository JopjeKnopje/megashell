/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:33:28 by jboeve            #+#    #+#             */
/*   Updated: 2023/11/25 12:40:04 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BUILD_TEST

int main(int argc, char *argv[], char *envp[])
{
	return megashell(argc, argv, envp);
}

#endif
