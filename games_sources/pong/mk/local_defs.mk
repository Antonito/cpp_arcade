# Definitions for Makefile
NAME=			$(ROOT_DIR)/games/libarcade_snake.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -rdynamic -L$(ROOT_DIR)/build -larcade_common -lgames_common

LOCAL_DEBUG_FLAGS=
