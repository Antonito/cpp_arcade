# Definitions for Makefile
NAME=			$(PROJECT_DIR)/lib/lib_arcade_allegro5.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared					\
			$(shell pkg-config --libs allegro-5)	\
			-L$(PROJECT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
