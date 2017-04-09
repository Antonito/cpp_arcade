# Definitions for Makefile
NAME=			$(ROOT_DIR)/games/pong.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -rdynamic -L$(ROOT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
