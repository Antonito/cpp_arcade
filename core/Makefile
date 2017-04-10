# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/
LOGGER_DIR=	$(SRC_DIR)logger/

DIR_LIST=	$(SRC_DIR)		\
		$(LOGGER_DIR)

# Project's files

SRC_FILES=	main.cpp		\
		GenLibrary.cpp		\
		Core.cpp

LOGGER_FILES=	Logger.cpp		\
		LogMessage.cpp		\
		LogSink.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))		\
		$(addprefix $(LOGGER_DIR), $(LOGGER_FILES))

INC_DIR=	$(DIR_LIST)				\
		$(ROOT_DIR)/common/src/			\
		$(ROOT_DIR)/network/src/			\
		$(ROOT_DIR)/games_sources/games_common/src/	\
		$(ROOT_DIR)/exceptions/src/

# Rules
include $(MK_COMMON_DIR)rules.mk
