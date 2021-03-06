/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduceup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 19:22:21 by nbouteme          #+#    #+#             */
/*   Updated: 2015/12/09 13:39:26 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <stdlib.h>

t_list	*ft_lstreduceup(const t_list *l, const t_list *init,
						void (*f)(t_list *, const t_list*, void *), void *up)
{
	t_list *acc;

	acc = ft_lstnew(init->content, init->content_size);
	while (l)
	{
		f(acc, l, up);
		l = l->next;
	}
	return (acc);
}
