/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.h                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/12 18:45:58 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/14 01:58:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
#include "plarser.h"

typedef struct s_exp {
	char	**envp;
	char	*s_exp;
	char	*end;
	size_t  step;
	size_t  i;
	t_token *t;
} t_exp;


// expander_utils.c
t_exp ex_pack_struct(t_token *t, char **envp);
bool ex_iterate(t_exp *exp);

// expander_utils2.c
size_t	ex_var_len(char *s);
size_t	get_key_len(char *key);
void	ex_step_into_quote(t_token *t);
char	*ex_find_var(char **envp, char *name, size_t len);
char	*ex_str_append(char *s_base, char *s_append, size_t append_size);


// expander.c
size_t	ex_var_len(char *s);
char	*ex_str_append(char *s_base, char *s_append, size_t append_size);
char	*expand_var(char **envp, t_token *t, size_t i);


#endif
