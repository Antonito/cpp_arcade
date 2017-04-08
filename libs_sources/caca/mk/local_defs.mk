# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_caca.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared				\
			$(shell pkg-config --libs caca)	\
			-L$(ROOT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
