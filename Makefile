.PHONY: all clean run

# Define required environment variables
PLATFORM              ?= PLATFORM_DESKTOP

# Define project variables
PROJECT_NAME          ?= pmg
PROJECT_VERSION       ?= 1.0
PROJECT_BUILD_PATH    ?= .

RAYLIB_PATH           ?= ../../raylib

# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX, BSD
RAYLIB_INCLUDE_PATH   ?= /usr/local/include
RAYLIB_LIB_PATH       ?= /usr/local/lib

# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE

# Define default C compiler: CC
#------------------------------------------------------------------------------------------------
CC = clang

CFLAGS = -std=c99 -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -D_DEBUG
else
    CFLAGS += -s -O2
endif

# Additional flags for compiler (if desired)
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes

# Define include paths for required headers: INCLUDE_PATHS
# NOTE: Some external/extras libraries could be required (stb, physac, easings...)
#------------------------------------------------------------------------------------------------
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I$(RAYLIB_PATH)/src/extras

# Define additional directories containing required header files
INCLUDE_PATHS += -I$(RAYLIB_INCLUDE_PATH)

# Define library paths containing required libs: LDFLAGS
#------------------------------------------------------------------------------------------------
LDFLAGS = -L. -L$(RAYLIB_PATH)/src -L$(RAYLIB_LIB_PATH)

# Define libraries required on linking: LDLIBS
# NOTE: To link libraries (lib<name>.so or lib<name>.a), use -l<name>
#------------------------------------------------------------------------------------------------
LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Define source code object files required
#------------------------------------------------------------------------------------------------
PROJECT_SOURCE_FILES ?= \
    main.c

# Define all object files from source files
OBJS = $(patsubst %.c, %.o, $(PROJECT_SOURCE_FILES))

# Default target entry
# NOTE: We call this Makefile target or Makefile.Android target
all: $(PROJECT_NAME)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

run: $(PROJECT_NAME)
	./$(PROJECT_NAME)

# Clean everything
clean:
	rm -fv *.o $(PROJECT_NAME)
