# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_ncurses.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared				\
			-lncurses			\
			-L$(ROOT_DIR)/build -larcade_common -larcade_exceptions

LOCAL_DEBUG_FLAGS=
