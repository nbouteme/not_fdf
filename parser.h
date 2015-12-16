#ifndef PARSER_H
#define PARSER_H

#include <libft.h>

char		**ft_strtok(const char *str, char c);

typedef struct	s_sparse_model
{
	t_list *verts;
	int w;
	int h;
}				t_sparse_model;

typedef struct	s_vertex
{
	int x;
	int y;
	int z;
	unsigned color;
}				t_vertex;

typedef struct	s_model
{
	t_vertex *verts;
	int *elements;
}				t_model;

t_sparse_model *parse_file(char **file);
t_model *flatten_model(t_sparse_model *sm);

#endif /* PARSER_H */
