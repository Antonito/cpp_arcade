# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

DIR_LIST=	$(SRC_DIR)			\
		$(SRC_DIR)exceptions/

# Project's files

SRC_FILES=	ASocket.cpp			\
		TCPSocket.cpp			\
		exceptions/AException.cpp	\
		exceptions/SockError.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST)

# Rules
include $(MK_COMMON_DIR)rules.mk
