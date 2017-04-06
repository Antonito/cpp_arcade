# Definitions for Makefile
NAME=			$(PROJECT_DIR)/arcade

INC_DIR=		$(PROJECT_DIR)/common/src/	\
			$(PROJECT_DIR)/network/src/

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-ldl -L$(PROJECT_DIR)/build/ -larcade_common -larcade_network

LOCAL_DEBUG_FLAGS=
