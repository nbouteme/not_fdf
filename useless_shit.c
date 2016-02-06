/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_shit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:51:15 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 04:07:16 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

void	present(t_graphics *g)
{
	mlx_put_image_to_window(g->d->conn, g->d->win, g->int_img, 0, 0);
}

void	clear_graphics(t_graphics *g)
{
	int max;
	int i;

	i = 0;
	max = g->dim.w * g->dim.h;
	ft_memset(g->fb, 0, max << 2);
/*	while (i < max)
	g->z[i++] = 0x3F800000;*/
}
