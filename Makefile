MK_DIR=			./mk/

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

###### Add your graphic libraries here #####
GFX_LIBS_DIR=		./libs/

GFX_LIBS=		

###### Add your games here #####
GAMES_DIR=		./games
GAMES=

###### Add your projects here #####
PROJECTS=		$(addprefix $(GFX_LIBS_DIR), $(GFX_LIBS))	\
			$(addprefix $(GAMES_DIR), $(GAMES))		\
			./core/

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
