/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:03:58 by joppe         #+#    #+#                 */
/*   Updated: 2023/07/31 17:03:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "megashell.h"

// prompt.c
void	prompt_env_setup();
char	*prompt_get_line();

// signals.c
void	sigals_setup();


#endif // !INPUT_H
