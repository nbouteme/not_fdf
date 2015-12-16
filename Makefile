#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2015/12/08 12:51:41 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

SRCDIR = .

INCDIR = libft minilibx

LIBDIR = libft minilibx

LIBS = libft.a
LINK = ft m mlx Xext X11

SRC = 	mat3.c		 	\
	 	mat4.c		 	\
		vec3.c		 	\
		proj.c		 	\
		str_utils.c		\
		parse_file.c	\
		flatten.c		\
		display.c		\
		main.c			\

OBJ = $(SRC:.c=.o)

CC = clang
OPT=-g
CFLAGS = -Wall -Wextra -Werror $(OPT)

LIBDIRS = $(addprefix -L, $(LIBDIR))
LLIBS = $(addprefix -l, $(LINK))
INCDIRS = $(addprefix -I, $(INCDIR))

ECHO = echo
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
ECHO = echo -e
endif

all: $(NAME)

libft/libft.a:
	@$(ECHO) "\033[0;34m[-] Building dependency" $@; make -C libft

minilibx/libmlx.a:
	@$(ECHO) "\033[0;34m[-] Building dependency" $@; make -C minilibx

%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INCDIRS) -c $^
	@$(ECHO) "\033[0;32m[✓] Built C object" $@

$(NAME): $(OBJ) libft/libft.a minilibx/libmlx.a
	@$(ECHO) "\033[0;34m--------------------------------"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBDIRS) $(LLIBS)
	@$(ECHO) "\033[0;31m[✓] Linked C executable" $(NAME)


.PHONY: clean fclean re cleandeps fcleandeps

cleandeps:
	@$(ECHO) "\033[0;33m[-] Cleaning dependency" libft.a; make -C libft clean
	@$(ECHO) "\033[0;33m[-] Cleaning dependency" libft.a; make -C minilibx clean

fcleandeps:
	rm -rf libft/libft.a minilibx/libmlx.a

clean: cleandeps
	@/bin/rm -rf $(OBJ)
	@$(ECHO) "\033[0;33m[✓] Removed object files" $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(ECHO) "\033[0;33m[✓] Removed executable" $(NAME)

re: fclean fcleandeps
	@$(MAKE) all
