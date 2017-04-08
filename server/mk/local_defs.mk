# Definitions for Makefile
NAME=			$(PROJECT_DIR)/server_arcade

INC_DIR=		$(PROJECT_DIR)/network/src/		\
			$(PROJECT_DIR)/network/src/exceptions	\
			$(PROJECT_DIR)/common/src

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-L$(PROJECT_DIR)/build/ -larcade_network -pthread

LOCAL_DEBUG_FLAGS=
