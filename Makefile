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
			x		\
			sfml_sound

GFX_PROJECT=		$(addprefix $(GFX_LIBS_DIR), $(GFX_LIBS))

###### Add your games here #####
GAMES_DIR=		./games_sources/

GAMES=			games_common	\
			snake		\
			centipede	\
			pacman		\
			pong

GAME_PROJECT=		$(addprefix $(GAMES_DIR), $(GAMES))

##### General configuration
COMMON=			common

CORE=			core

NETWORK=		network

SERVER=			server

EXCEPTIONS=		exceptions

###### Add your projects here #####
PROJECTS=		./$(COMMON)/					\
			./$(EXCEPTIONS)					\
			./$(NETWORK)/					\
			$(GFX_PROJECT)					\
			$(GAME_PROJECT)					\
			./$(CORE)/					\
			./$(SERVER)/

# Some useful variables
DEBUG=			no

ARGS=			DEBUG=$(DEBUG) -s --warn-undefined-variables -C

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

$(EXCEPTIONS):
			@$(ECHO) "$(YELLOW)./$(EXCEPTIONS)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(EXCEPTIONS)

$(NETWORK):
			@$(ECHO) "$(YELLOW)./$(NETWORK)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(NETWORK)

$(CORE):
			@$(ECHO) "$(YELLOW)./$(CORE)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(CORE)

$(SERVER):
			@$(ECHO) "$(YELLOW)./$(SERVER)/ :$(CLEAR)\n"
			@$(MAKE) $(ARGS) $(SERVER)

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

re:
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
