# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_allegro5.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared									\
			$(shell pkg-config --libs allegro-5 allegro_ttf-5 allegro_image-5)	\
			-L$(ROOT_DIR)/build -larcade_common -larcade_exceptions

LOCAL_DEBUG_FLAGS=
