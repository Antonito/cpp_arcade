# Definitions for Makefile
NAME=			$(PROJECT_DIR)/server_arcade

INC_DIR=		$(PROJECT_DIR)/network/src/

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-L$(PROJECT_DIR)/build/ -larcade_network

LOCAL_DEBUG_FLAGS=
