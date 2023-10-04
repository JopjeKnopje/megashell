/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:31:17 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 02:22:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "megashell.h"
#include "plarser.h"
#include "builtins.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

uint8_t	read_from_heredoc(char *close_line, int pipe_fd);
bool	handle_heredoc(t_cmd_frame *f);
bool	redirections(t_cmd_frame *f);

#endif
