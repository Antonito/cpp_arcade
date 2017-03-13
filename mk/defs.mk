# Commands definitions
RM=		rm -f
ECHO=		echo -ne
RANLIB=		ar rcs
CP=		cp
CHDIR=		cd

ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)

# Compilation and link definitions
CXX=		clang
CPP_VER=	c++14

# Debug Infos | -lasan needs to be first
ifeq ($(DEBUG), yes)
CXXFLAGS=	-g -DDEBUG -fomit-frame-pointer 	\
		-fstack-protector			\
		-Wformat-security			\
		$(LOCAL_DEBUG_FLAGS)
LDFLAGS=	-g					\
		-Wl,-z,relro				\
		-Wl,-z,now				\
		-Wl,--no-undefined			\
		-L/usr/lib/clang/3.8.1/lib/linux/	\
		-lasan					\
		-lclang_rt.ubsan_standalone-x86_64	\
		-lclang_rt.ubsan_standalone_cxx-x86_64	\
		-rdynamic				\
		-ldl					\
		-lrt
else
CXXFLAGS=	-DNDEBUG
LDFLAGS=
endif

CXXFLAGS+=	$(INC_DIR)			\
		$(LOCAL_COMP_FLAGS)

LDFLAGS+=	-lstdc++			\
		$(LOCAL_LINK_FLAGS)

ifeq ($(CXX),clang)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra -fno-exceptions
LDFLAGS+=
else ifeq ($(CXX),g++)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra
LDFLAGS+=
else
CXXFLAGS+=
LDFLAGS+=
endif
