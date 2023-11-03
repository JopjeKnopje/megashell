/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:33:28 by jboeve            #+#    #+#             */
/*   Updated: 2023/11/03 16:26:09 by jboeve        ########   odam.nl         */
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

#endif /* ifndef BUILD_TEST */
