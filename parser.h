#ifndef PARSER_H
#define PARSER_H

#include <libft/math.h>
#include <libft/mlx.h>

t_sparse_model *parse_file(char **file);
t_model *flatten_model(t_sparse_model *sm);

#endif /* PARSER_H */
