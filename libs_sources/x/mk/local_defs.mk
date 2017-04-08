# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_x.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared				\
			$(shell pkg-config --libs x11)	\
			-L$(ROOT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
