/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:31:17 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/30 17:24:40 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "megashell.h"
#include "plarser.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

t_cmd_frame	*handle_redir_input(t_cmd_list *cmd_list);
void		handle_redir_output(t_cmd_frame *cmd_frame);
void	redirects(t_cmd_list *cmd_list, int pipe_fd[2]);
void		read_from_heredoc(char *close_line, int pipe_fd);
void		handle_heredoc(t_cmd_frame *cmd_frame);

#endif