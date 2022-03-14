
CPP=g++

# -Wall -g3
# pmap $(ps -o pid,command ax | grep metro | cut -d ' ' -f 3 | sed "1q")

OBJS = src/*.cpp

COMPILER_FLAGS = 

LINKER_FLAGS = -lyaml-cpp -lglfw -lGLEW -lGL -lX11 -lGLU -lOpenGL -lglut

all: options msc

options:
	@echo msc build options:
	@echo "CPP      = $(CPP)"
	@echo "OBJS     = $(OBJS)"
	@echo "CFLAGS   = $(COMPILER_FLAGS)"
	@echo "LFLAGS   = $(LINKER_FLAGS)"


msc: options clean
	$(CPP) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

clean:
	rm -f i3sb