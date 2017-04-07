# Definitions for Makefile
NAME=			$(PROJECT_DIR)/games/pong.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -rdynamic -L$(PROJECT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
