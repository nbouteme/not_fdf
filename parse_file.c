#include <libft.h>
#include <stdlib.h>

#include "parser.h"

/*
** file    := <line> <newline> [ <line> <newline> ]
** line    := <vertice> [ <space>... <vertice> ]
** vertice := <height> [,color]
** height  := entier en texte
** color   := 0xRRGGBB
** space   := ' '
** newline := '\n'
 */

int parse_height(char **file, t_vertex *v)
{
	v->z = ft_atoi(*file);
	*file += **file == '-';
	while(ft_isdigit(*file[0]))
		file[0]++;
	return **file == ' ' || **file == '\n' || !**file;
}

unsigned ft_atoi_base(const char *s, int base)
{
	const char *b = "0123456789ABCDEF";
	int i;

	i = 0;
	while (ft_strindexof(b, *s) != -1)
	{
		i += ft_strindexof(b, *s++);
		if (ft_strindexof(b, *s) == -1)
			break ;
		i *= base;
	}
	return (i);
}

int parse_color(char **file, t_vertex *v)
{
	*file += **file == '0';
	*file += **file == 'x';
	v->color = ft_atoi_base(*file, 16);
	while(ft_isdigit(*file[0]) || ('A' <= *file[0] && *file[0] <= 'Z'))
		file[0]++;
	return **file == ' ' || **file == '\n' || !**file;
}

int parse_vertex(char **file, t_sparse_model *m)
{
	t_vertex v;
	if(!parse_height(file, &v))
		return 0;
	if(*file[0] == ',' && parse_color(file, &v))
		return 0;
	ft_lstpush(&m->verts, ft_lstnew(&v, sizeof(v)));
	return 1;
}

#include <stdio.h>

int parse_line(char *line, t_sparse_model *m)
{
	int tmp;

	tmp = 0;
	while(1)
	{
		if(!parse_vertex(&line, m))
			return 0;
		else
			++tmp;
		while(*line == ' ')
			line++;
		if(!*line)
			break ;
	}
	m->w = m->w ? m->w : tmp;
	return tmp == m->w;
}

t_sparse_model *parse_file(char **file)
{
	t_sparse_model *m;

	m = ft_memset(malloc(sizeof(*m)), 0, sizeof(*m));
	while (1)
	{
		if(!parse_line(*file++, m))
			return 0;
		m->h++;
		if(ft_strcmp(*file++, "\n") != 0)
			return 0;
		if(!*file)
			break ;
	}
	return m;
}
