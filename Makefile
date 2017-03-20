MK_DIR=			./mk/

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

###### Add your graphic libraries here #####
GFX_LIBS_DIR=		./libs_sources/

GFX_LIBS=		sdl

###### Add your games here #####
GAMES_DIR=		./games_sources/

GAMES=			games_common		\
			snake

###### Add your projects here #####
PROJECTS=		./common/					\
			$(addprefix $(GFX_LIBS_DIR), $(GFX_LIBS))	\
			$(addprefix $(GAMES_DIR), $(GAMES))		\
			./core/

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

.PHONY: all clean fclean re infos
