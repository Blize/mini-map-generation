# Define the default compiler and flags
CC = clang
CFLAGS = -std=c99 -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE

# Define the project name and source file
PROJECT_NAME = pmg
PROJECT_SOURCE = main.c

RAYLIB_PATH = ../../raylib
INCLUDE_PATHS = -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I$(RAYLIB_PATH)/src/extras
LDFLAGS = -L$(RAYLIB_PATH)/src -L$(RAYLIB_PATH)/src/platform

# Define the libraries required on linking
LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Define the build mode (DEBUG or RELEASE)
BUILD_MODE = RELEASE

# Define the object files
OBJS = $(PROJECT_SOURCE:.c=.o)

# Default target
all: $(PROJECT_NAME)

# Build the project
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)

# Compile source files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

# Run the project
run: $(PROJECT_NAME)
	./$(PROJECT_NAME)

# Clean everything
clean:
	rm -fv *.o $(PROJECT_NAME)
