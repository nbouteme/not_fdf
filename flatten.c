/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:37:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:40:27 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <libft/math.h>
#include "parser.h"

size_t	fillelem(t_vertex *vertptr, int *elemptr, t_sparse_model *sm)
{
	int i;
	int j;
	int *e;

	e = elemptr;
	i = -1;
	while (++i < sm->h && (j = -1))
		while (++j < sm->w)
		{
			vertptr->x = j;
			vertptr->y = i;
			++vertptr;
			if (j < sm->w - 1)
			{
				*elemptr++ = (i * sm->w) + j;
				*elemptr++ = (i * sm->w) + j + 1;
			}
			if (i < sm->h - 1)
			{
				*elemptr++ = (i * sm->w) + j;
				*elemptr++ = ((i + 1) * sm->w) + j;
			}
		}
	return (elemptr - e);
}

void	fill_vert_array(t_dlist *elem, void *up)
{
	t_vertex **verts;

	verts = up;
	ft_memcpy(verts[0], elem->content, sizeof(t_vertex));
	verts[0]++;
}

/*
** Pour un sommet s d'indice [x, y], on doit effectuer au maximum 2
** trace de segment: un de s a t, d'indice [x + 1, y] ssi s n'est pas
** le dernier de sa ligne et de s a u, d'indice [x, y + 1], ssi s
** n'est pas sur la derniere ligne Les 2 dimensions sont sur un seul
** tableau, pour acceder a une coordonnee [x, y], on accede a la case
** [y * length + x] Le format de elements est une collection de paires
** d'indice des sommets a relier La taille de elem est determine de la
** facon suivante: Pour une map de w*h, il y a (w-1 * h-1) sommet qui
** genere 2 segment, w qui en generent 1, h qui en genere 1, et un qui
** n'en genere pas.  t = (2 * (w - 1 * h - 1)) + w - 1 + h - 1. pour
** une 3*3: t = (3 * (w - 1 * h - 1)) = 12 segment pour une 3*3: t =
** (3 * (1) + 1) = 12 segment pour une 3*3: un segment est une paire
** d'int, donc il faut allouer 2 * sizeof int * 12
*/

void	free_verts(void *d, size_t s)
{
	(void)s;
	free(d);
}

t_model	*flatten_model(t_sparse_model *sm)
{
	t_model		*ret;
	t_vertex	*vertptr;
	t_vec3		pos;

	ret = malloc(sizeof(*ret));
	ret->verts = malloc(sizeof(t_vertex) * sm->h * sm->w);
	vertptr = ret->verts;
	ftext_lstiterup(sm->verts, &fill_vert_array, (void*)&vertptr);
	ret->elements = malloc(8 * ((2 * sm->w * sm->h) - sm->w - sm->h));
	ret->e_sz = fillelem(ret->verts, ret->elements, sm);
	ret->w = sm->w;
	ret->h = sm->h;
	pos = ft_memalloc(sizeof(*pos));
	(*pos)[0] = -ret->w / 2;
	(*pos)[1] = -ret->h / 2;
	ret->model = translation(vec3_zero());
	free(pos);
	ftext_lstdel(&sm->verts, &free_verts);
	free(sm);
	return (ret);
}
