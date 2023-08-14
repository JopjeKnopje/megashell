/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 10:05:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 10:07:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

typedef struct s_command_frame {
	char **argv;
	int infile;
	int outfile;
} t_command_frame;

typedef struct e_cf_list {
	t_command_frame		content;
	struct e_cf_list	*next;
}	t_cf_list;

#endif // !PARSER_H
