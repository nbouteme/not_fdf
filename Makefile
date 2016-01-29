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
OPTS =	-O3 -march=native -mtune=native -ffinite-math-only \
	-funsafe-math-optimizations -fno-math-errno -ffast-math \
	-lm -Lminilibx -lmlx
UNAME := $(shell uname)
#$(shell make -s -C minilibx)
ifeq ($(UNAME), Linux)
OPTS += -lX11 -lXext
else
OPTS += -framework OpenGL -framework AppKit
endif

#OPTS = -g

##################
include mkgen.mk #
##################
