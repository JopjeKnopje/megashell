/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:58 by joppe             #+#    #+#             */
/*   Updated: 2024/02/07 11:56:18 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "megashell.h"

typedef enum e_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE,
}	t_signal;

// signals.c
bool		set_signal_mode(int mode);

// prompt.c
const char	*get_prompt(int exit_code);

#endif
