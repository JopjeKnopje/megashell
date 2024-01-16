#ifndef TEST_UTILS_H
# define TEST_UTILS_H
# include <unistd.h>
# include "plarser.h"

void		print_bits(size_t const size, void const *const ptr);
void		print_2d_arr(char **s, char *name);
void		print_cf_list(t_cmd_list *list);
void		print_token(t_token t);
void		print_tokens(t_tok_list *lst);
void		print_cmds(t_cmd_list *cmds);
const char	*get_token_name(t_token_kind k);

#endif 
