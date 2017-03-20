# Definitions for Makefile
NAME=			$(PROJECT_DIR)/build/libgames_common.a

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-L$(PROJECT_DIR)/build/ -larcade_common

LOCAL_DEBUG_FLAGS=
