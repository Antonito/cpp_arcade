# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/
NET_DIR=	$(SRC_DIR)network/
EXCEPT_DIR=	$(SRC_DIR)exceptions/
LOGGER_DIR=	$(SRC_DIR)logger/

DIR_LIST=	$(SRC_DIR)		\
		$(NET_DIR)		\
		$(EXCEPT_DIR)		\
		$(LOGGER_DIR)

# Project's files

SRC_FILES=	main.cpp		\
		GenLibrary.cpp		\
		Core.cpp

NET_FILES=	ASocket.cpp		\
		TCPSocket.cpp

EXCEPT_FILES=	AException.cpp		\
		SockError.cpp

LOGGER_FILES=	Logger.cpp		\
		LogMessage.cpp		\
		LogSink.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))		\
		$(addprefix $(NET_DIR), $(NET_FILES))		\
		$(addprefix $(EXCEPT_DIR), $(EXCEPT_FILES))	\
		$(addprefix $(LOGGER_DIR), $(LOGGER_FILES))		

# Rules
include $(MK_COMMON_DIR)rules.mk
