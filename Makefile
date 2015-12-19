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

OPTS = -g

SRC = 	mat3.c		 	\
	 	mat4.c		 	\
		vec3.c		 	\
		vec4.c		 	\
		proj.c		 	\
		str_utils.c		\
		parse_file.c	\
		flatten.c		\
		display.c		\
		graphics.c		\
		clip.c		\
		main.c			\

LIBS = m

#******************************************************************************#

include mkgen.mk
