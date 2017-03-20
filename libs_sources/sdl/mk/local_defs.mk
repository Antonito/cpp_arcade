# Definitions for Makefile
NAME=			$(PROJECT_DIR)/lib/lib_arcade_sdl.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -lSDL2 -L$(PROJECT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
