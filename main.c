#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>

#define B_SIZE (1 << 16)

#include "parser.h"
#include "display.h"

int check_input(char *s)
{
	const char *auth = " \n0123456789-xABCDEF";
	while(*s)
		if(ft_strindexof(auth, *s) == -1)
			return 0;
		else
			++s;
	return 1;
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
		if(!check(buf))
			return 0;
		tmp = ret;
		ft_bzero(buf + n, B_SIZE - n);
		ret = ft_strjoin(ret, buf);
		free(tmp);
	}
	return (ret);
}

#include <mlx.h>
int main(int argc, char **argv)
{
	int fd;
	if(argc <= 1)
		return 1;
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		return 2;
	char *file = readfile(fd, &check_input);

	if(!file)
		return 1;

	char **a_file = ft_strtok(file, '\n');
	t_sparse_model *sm = parse_file(a_file);

	t_model *m = flatten_model(sm);

	run_display(new_display(m));
	printf("%p\n", m);
}
