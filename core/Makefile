# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's files

SRC_DIR=	./src/
NET_DIR=	$(SRC_DIR)network/
EXCEPT_DIR=	$(SRC_DIR)exceptions/

SRC_FILES=	main.cpp		\
		GenLibrary.cpp

NET_FILES=	ASocket.cpp		\
		TCPSocket.cpp

EXCEPT_FILES=	AException.cpp		\
		SockError.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))	\
		$(addprefix $(NET_DIR), $(NET_FILES))	\
		$(addprefix $(EXCEPT_DIR), $(EXCEPT_FILES))

# Rules
include $(MK_COMMON_DIR)rules.mk
