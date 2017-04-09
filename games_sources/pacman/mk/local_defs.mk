# Definitions for Makefile
NAME=			$(PROJECT_DIR)/games/libarcade_pacman.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -rdynamic -L$(PROJECT_DIR)/build -larcade_common -lgames_common

LOCAL_DEBUG_FLAGS=
