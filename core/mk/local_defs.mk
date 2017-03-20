# Definitions for Makefile
NAME=			$(PROJECT_DIR)/arcade

INC_DIR=		-I$(PROJECT_DIR)/common/src/

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-ldl -L$(PROJECT_DIR)/build/ -larcade_common

LOCAL_DEBUG_FLAGS=
