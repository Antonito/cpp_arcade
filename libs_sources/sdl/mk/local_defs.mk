# Definitions for Makefile
NAME=			../../lib/lib_arcade_sdl.so

LOCAL_COMP_FLAGS=	-fPIC

ifeq ($(UNAME_S),Darwin)
LOCAL_LINK_FLAGS=	-shared -F/Library/Frameworks -framework SDL2
else
LOCAL_LINK_FLAGS=	-shared -lSDL2
endif

LOCAL_DEBUG_FLAGS=
