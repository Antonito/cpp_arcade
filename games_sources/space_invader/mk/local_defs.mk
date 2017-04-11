# Definitions for Makefile
NAME=			$(ROOT_DIR)/games/lib_arcade_space_invader.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared -rdynamic -L$(ROOT_DIR)/build -larcade_common -lgames_common -larcade_exceptions

LOCAL_DEBUG_FLAGS=
