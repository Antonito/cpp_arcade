# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=		./src/

DIR_LIST=	$(SRC_DIR)

# Project's files

SRC_FILES=	Blockade.cpp	\
		EntryPoint.cpp	\
		Player.cpp	\
		Fruit.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST)					\
		$(ROOT_DIR)/common/src/			\
		$(ROOT_DIR)/games_sources/games_common/src/

# Rules
include $(MK_COMMON_DIR)rules.mk
