/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 17:15:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/07/31 18:56:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H


typedef enum e_token_type {
	TOKEN_UNKNOWN,
}	t_token_type;

typedef struct e_token {
	t_token_type type;
	char *content;
}	t_token;


// lexer.c
t_token lexer(char *s);

#endif // !LEXER_H
