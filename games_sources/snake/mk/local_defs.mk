# Definitions for Makefile
NAME=			$(PROJECT_DIR)/games/snake.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-L$(PROJECT_DIR)/build -lgames_common -larcade_common -shared -rdynamic

LOCAL_DEBUG_FLAGS=
