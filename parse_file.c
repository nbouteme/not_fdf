/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:42:29 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 03:16:46 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

/*
** file    := <line> <newline> [ <line> <newline> ]...
** line    := <vertice> [ <space>... <vertice> ]
** vertice := <height> [,color]
** height  := entier en texte
** color   := 0x[[RR]GG]BB
** space   := ' '
** newline := '\n'
*/

int				parse_height(char **file, t_vertex *v)
{
	if (!(ft_isdigit(*file[0]) || *file[0] == '-'))
		return (0);
	v->z = ft_atoi(*file);
	*file += **file == '-';
	while (ft_isdigit(*file[0]))
		file[0]++;
	return (**file == ',' || **file == ' ' || **file == '\n' || !**file);
}

int				parse_color(char **file, t_vertex *v)
{
	const char	*b = "0123456789ABCDEF";
	char		*s;

	(*file)++;
	*file += **file == '0';
	*file += **file == 'x';
	s = *file;
	v->color = 0;
	while (ft_strindexof(b, ft_toupper(*s)) != -1)
	{
		v->color += ft_strindexof(b, ft_toupper(*s++));
		if (!*s || ft_strindexof(b, ft_toupper(*s)) == -1)
			break ;
		v->color <<= 4;
	}
	while (ft_isdigit(*file[0]) || ('A' <= ft_toupper(*file[0]) &&
									ft_toupper(*file[0]) <= 'Z'))
		file[0]++;
	return (**file == ' ' || **file == '\n' || !**file);
}

int				parse_vertex(char **file, t_sparse_model *m)
{
	t_vertex	v;

	v.color = 0x00FFFFFF;
	if (!parse_height(file, &v))
	{
		puts("Malformed height");
		return (0);
	}
	if (*file[0] == ',' && !parse_color(file, &v))
	{
		puts("Malformed color");
		return (0);
	}
	ftext_lstpush_back(m->verts, ftext_lstnewelem(&v, sizeof(v)));
	return (1);
}

int				parse_line(char *line, t_sparse_model *m)
{
	int tmp;

	tmp = 0;
	while (1)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		if (!parse_vertex(&line, m))
			return (0);
		++tmp;
		if (!*line)
			break ;
	}
	m->w = m->w ? m->w : tmp;
	if (!(tmp == m->w))
	{
		printf("Different length");
		return (0);
	}
	return (tmp == m->w);
}

t_sparse_model	*parse_file(char **file)
{
	t_sparse_model *m;

	m = ft_memalloc(sizeof(*m));
	m->verts = ftext_lstnew();
	while (*file)
	{
		if (!parse_line(*file++, m))
			return (0);
		m->h++;
		if (!*file || ft_strcmp(*file++, "\n") != 0)
			return (0);
		if (!*file)
			break ;
	}
	printf("%d, %d\n", m->w, m->h);
	if (m)
		return (m->w * m->h > 1 ? m : 0);
	return (0);
}
