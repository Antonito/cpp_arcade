# Definitions for Makefile
NAME=			$(ROOT_DIR)/server_arcade

INC_DIR=		$(ROOT_DIR)/network/src/

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-L$(ROOT_DIR)/build/ -larcade_network -pthread

LOCAL_DEBUG_FLAGS=
