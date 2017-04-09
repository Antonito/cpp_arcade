# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk $(MK_DIR)local_defs.mk

# Project's directories

SRC_DIR=		./src/

DIR_LIST=	$(SRC_DIR)

ifeq ($(UNAME_S),Darwin)
DIR_LIST+=	/Library/Frameworks/SDL2.framework/Headers/	\
		/Library/Frameworks/SDL2_ttf.framework/Headers/
endif

# Project's files

SRC_FILES=	LibSDL.cpp		\
		EntryPoint.cpp		\
		KeysMapping.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST)			\
		$(ROOT_DIR)/common/src/	\
		$(ROOT_DIR)/exceptions/src/

# Rules
include $(MK_COMMON_DIR)rules.mk
