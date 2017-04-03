MK_DIR=			./mk/

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

LINK_INTERFACE=		./link_interface.sh

###### Add your graphic libraries here #####
GFX_LIBS_DIR=		./libs_sources/

GFX_LIBS=		allegro5	\
			ncurses		\
			sdl		\
			sfml		\
			caca		\
			lapin		\
			x

GFX_PROJECT=		$(addprefix $(GFX_LIBS_DIR), $(GFX_LIBS))

###### Add your games here #####
GAMES_DIR=		./games_sources/

GAMES=			snake

GAME_PROJECT=		$(addprefix $(GAMES_DIR), $(GAMES))

##### General configuration
COMMON=			common

CORE=			core

###### Add your projects here #####
PROJECTS=		./$(COMMON)/					\
			$(GFX_PROJECT)					\
			$(GAME_PROJECT)					\
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

gfx:
			@$(foreach path, $(GFX_PROJECT),		\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) re;)

games:
			@$(foreach path, $(GAME_PROJECT),		\
			$(PRINT_DIR)					\
			$(MAKE) $(ARGS) $(path) re;)

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
			git submodule foreach git pull origin master

.PHONY: all clean fclean re infos $(GAMES) $(GFX_LIBS) $(COMMON) $(CORE)
