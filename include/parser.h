// /* ************************************************************************** */
// /*                                                                            */
// /*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
// /*                                                    +:+                     */
// /*   By: joppe <jboeve@student.codam.nl>             +#+                      */
// /*                                                  +#+                       */
// /*   Created: 2023/08/14 10:05:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 12:30:19 by jboeve        ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */
//
//
// #ifndef PARSER_H
// #define PARSER_H
//
//
// typedef enum e_redir {
// 	REDIR_STDOUT = 0x0000,
// 	REDIR_PIPE = 0x0001,
// 	REDIR_STDIN = 0x0020,
// } t_io;
//
// // 0000
// // 
//
//
// // if infile and outfile are set read from them otherwise just stdin/stdout
// // if `is_piped` is set it overrules the outfile.
// typedef struct s_command_frame {
// 	char **argv;
// 	char *infile;
// 	char *outfile;
// 	bool is_piped;
//
//
// } t_command_frame;
//
// typedef struct e_cf_list {
// 	t_command_frame		content;
// 	struct e_cf_list	*next;
// }	t_cf_list;
//
//
// // parser_list.c
// void		pr_lstadd_back(t_cf_list **lst, t_cf_list *new);
// t_cf_list	*pr_lstnew(t_command_frame content);
// t_cf_list	*pr_lstlast(t_cf_list *lst);
//
// #endif // !PARSER_H
