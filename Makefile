MK_DIR=			./mk/

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

LINK_INTERFACE=		./link_interface.sh

###### Add your graphic libraries here #####
GFX_LIBS_DIR=		./libs_sources/

GFX_LIBS=		allegro5	\
			sdl		\
			sfml		\
			caca		\
			ncurses		\
			lapin		\
			x

###### Add your games here #####
GAMES_DIR=		./games_sources/

GAMES=			snake

COMMON=			common

CORE=			core

###### Add your projects here #####
PROJECTS=		./$(COMMON)/					\
			$(addprefix $(GFX_LIBS_DIR), $(GFX_LIBS))	\
			$(addprefix $(GAMES_DIR), $(GAMES))		\
			./$(CORE)/

# Some useful variables
DEBUG=			no

PROJECT_DIR=		${PWD}
ARGS=			DEBUG=$(DEBUG) PROJECT_DIR=$(PROJECT_DIR) -s --warn-undefined-variables -C

CURRENT_DIR=		${PWD}

PRINT_DIR=		$(ECHO) "$(YELLOW)$(path) :$(CLEAR)\n";

# Rules

all:
			@$(foreach path, $(PROJECTS),			\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path);)

$(GAMES):
			@$(ECHO) "$(YELLOW)$(GAMES_DIR)$@ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(GAMES_DIR)$@

$(GFX_LIBS):
			@$(ECHO) "$(YELLOW)$(GFX_LIBS_DIR)$@ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(GFX_LIBS_DIR)$@

$(COMMON):
			@$(ECHO) "$(YELLOW)./$(COMMON)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(COMMON)

$(CORE):
			@$(ECHO) "$(YELLOW)./$(CORE)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(CORE)

clean:
			@$(foreach path, $(PROJECTS),			\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) clean;)

fclean:
			@$(foreach path, $(PROJECTS),			\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) fclean;)

re:			link
			@$(foreach path, $(PROJECTS),			\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) re;)

infos:
			@$(foreach path, $(PROJECTS),			\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) infos;)

link:
			@$(LINK_INTERFACE)

# Update every dependency
update:
			git pull --recurse-submodules

.PHONY: all clean fclean re infos $(GAMES) $(GFX_LIBS) $(COMMON) $(CORE)
