#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    mkgen.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2015/12/08 12:51:41 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.SUFFIXES:

CC = clang
CFLAGS = -Wall -Wextra -Werror $(OPTS)
OBJ = $(SRC:.c=.o)

ECHO = echo
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
ECHO = echo -e
endif

PHONY=

FOLDERS = $(shell find . -maxdepth 1 -type d -printf %f\\n | tail -n +2 | grep -v ^cfg$ | grep -v ^\\.$ )
$(foreach f, $(FOLDERS), $(if $(or $(shell stat $f/$f.mk 2>/dev/null), $(shell stat cfg/$f.mk 2>/dev/null)), $(eval DEPS += $f)))

all: $(DEPS)
	@$(MAKE) -s $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCDIRS) -c $^
	@$(ECHO) "\033[0;32m[✓] Built C object" $@

$(NAME): $(OBJ)
	@$(ECHO) "\033[0;34m--------------------------------"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBDIRS) $(addprefix -l,$(LIBS)) $(INCDIRS)
	@$(ECHO) "\033[0;31m[✓] Linked C executable" $(NAME)

clean:
	@/bin/rm -rf $(OBJ)
	@$(ECHO) "\033[0;33m[✓] Removed object files" $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(ECHO) "\033[0;33m[✓] Removed executable" $(NAME)

re: fclean
	@$(MAKE) all

define generate_dep_rule
$1: $1/$(P_OUTPUT)

$1/$(P_OUTPUT):
	@$(ECHO) "\033[0;34m[-] Checking dependency " $(1)
	@$(MAKE) -s -C $(P_FOLDER)
endef

define def_rules
$(eval include cfg/$1.mk)
INCDIRS += $(addprefix -I, $(P_INCDIRS))
LIBDIRS += $(addprefix -L, $(P_LDIRS))
PHONY += $1
$(call generate_dep_rule,$1);
endef

$(foreach dep, $(DEPS), $(eval $(call def_rules,$(dep))))

.PHONY: clean fclean re cleandeps fcleandeps $(PHONY)
