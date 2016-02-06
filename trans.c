/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 01:34:37 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 04:26:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

static void	clip_3d(t_vec4 v1, t_vec4 v2)
{
	float	n;

	n = ((*v1)[3] - 0.01f) / ((*v1)[3] - (*v2)[3]);
	(*v2)[0] = ((1.0f - n) * (*v1)[0]) + (n * (*v2)[0]);
	(*v2)[1] = ((1.0f - n) * (*v1)[1]) + (n * (*v2)[1]);
	(*v2)[2] = ((1.0f - n) * (*v1)[2]) + (n * (*v2)[2]);
	(*v2)[3] = 0.1f;
}

static int	clip_plane(t_display *d, t_mat4 mvp, t_vec4 *rarb)
{
	t_vec4	a;
	t_vec4	b;

	a = mat4_m_vec4(mvp, rarb[0]);
	b = mat4_m_vec4(mvp, rarb[1]);
	rarb[2] = a;
	rarb[3] = b;
	if (((*a)[3] <= 0.1f) && ((*b)[3] <= 0.1f))
		return (0);
	if (((*a)[3] >= 0.1f) && ((*b)[3] < 0.1f))
		clip_3d(a, b);
	else if (((*a)[3] <= 0.1f) && ((*b)[3] > 0.1f))
		clip_3d(b, a);
	rarb[2] = to_screen_space(d->dim, vec4_sdiv(a, (*a)[3]));
	rarb[3] = to_screen_space(d->dim, vec4_sdiv(b, (*b)[3]));
	return (1);
}

void		render_line(t_display *d, t_mat4 mvp, t_vertex *ptr)
{
	t_vertex	a;
	t_vertex	b;
	t_vec4		papbrarb[4];
	int			i;
	t_drawpara	*p;

	i = 0;
	p = draw_para_ctl();
	while (i < (2 * (2 * (d->model->h) * (d->model->w)
					- d->model->w - d->model->h)))
	{
		a = ptr[d->model->elements[i++]];
		b = ptr[d->model->elements[i++]];
		papbrarb[0] = &(float[]){a.x, a.y, a.z, 1};
		papbrarb[1] = &(float[]){b.x, b.y, b.z, 1};
		p->c1 = a.color;
		p->c2 = b.color;
		if (clip_plane(d, mvp, papbrarb))
			draw_line(d->g, (t_point){(*papbrarb[2])[0], (*papbrarb[2])[1],
						(*papbrarb[2])[2]},
					(t_point){(*papbrarb[3])[0], (*papbrarb[3])[1],
							(*papbrarb[3])[2]});
		free(papbrarb[2]);
		free(papbrarb[3]);
	}
}
