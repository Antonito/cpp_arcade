# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk $(MK_DIR)local_defs.mk

# Project's directories

SRC_DIR=		./src/
COMMON_DIR=		$(SRC_DIR)common/
LIBS_COMMON_DIR=	$(SRC_DIR)libs_common/

DIR_LIST=	$(SRC_DIR)		\
		$(COMMON_DIR)		\
		$(LIBS_COMMON_DIR)

ifeq ($(UNAME_S),Darwin)
DIR_LIST+=	/Library/Frameworks/SDL2.framework/Headers/
endif

# Project's files

SRC_FILES=	LibSDL.cpp		\
		EntryPoint.cpp		\
		KeysMapping.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(addprefix -I,$(DIR_LIST))

# Rules
include $(MK_COMMON_DIR)rules.mk
