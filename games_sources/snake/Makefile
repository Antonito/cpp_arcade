# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=		./src/
COMMON_DIR=		$(SRC_DIR)common/
GAMES_COMMON_DIR=	$(SRC_DIR)games_common/

DIR_LIST=	$(SRC_DIR)		\
		$(COMMON_DIR)		\
		$(GAMES_COMMON_DIR)

# Project's files

SRC_FILES=		Snake.cpp

GAMES_COMMON_FILES=	AGame.cpp	\
			Layer.cpp	\
			Map.cpp		\
			SpriteRef.cpp	\
			Tile.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))	\
		$(addprefix $(GAMES_COMMON_DIR), $(GAMES_COMMON_FILES))

INC_DIR=	$(addprefix -I,$(DIR_LIST))

# Rules
include $(MK_COMMON_DIR)rules.mk
