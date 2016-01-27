/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:42:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:42:13 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <libft/std.h>
#include <libft/mlx.h>

#define B_SIZE (1 << 16)

#include "parser.h"

int		check_input(char *s)
{
	const char *auth = " \n0123456789-,xABCDEF";

	while (*s)
		if (ft_strindexof(auth, *s) == -1)
			return (0);
		else
			++s;
	return (1);
}

char	*readfile(int fd, int (*check)(char *))
{
	char	*buf;
	char	*tmp;
	char	*ret;
	int		n;

	ret = ft_strnew(1);
	buf = ft_strnew(B_SIZE + 1);
	while ((n = read(fd, buf, B_SIZE)) > 0)
	{
		if (!check(buf))
			return (0);
		tmp = ret;
		ft_bzero(buf + n, B_SIZE - n);
		ret = ft_strjoin(ret, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

int		main(int argc, char **argv)
{
	int				fd;
	char			*file;
	char			**a_file;
	t_sparse_model	*sm;
	t_model			*m;

	if (argc <= 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (2);
	file = readfile(fd, &check_input);
	if (!file)
		return (3);
	a_file = ft_strtok(file, '\n');
	sm = parse_file(a_file);
	if (!sm)
		return (4);
	m = flatten_model(sm);
	run_display(new_display(m));
}
