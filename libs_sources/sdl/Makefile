# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=		./src/
COMMON_DIR=		$(SRC_DIR)common/
LIBS_COMMON_DIR=	$(SRC_DIR)libs_common/

DIR_LIST=	$(SRC_DIR)		\
		$(COMMON_DIR)		\
		$(LIBS_COMMON_DIR)

# Project's files

SRC_FILES=	LibSDL.cpp		\
		EntryPoint.cpp		\
		KeysMapping.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(addprefix -I,$(DIR_LIST))

# Rules
include $(MK_COMMON_DIR)rules.mk
