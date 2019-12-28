CC = g++
CCFLAGS =
LIBS = -lglut -lGLU -lGL
TARGETS = project4.cpp, sandbox.cpp

.PHONY: all
all:
	$(info $(TARGETS))

# Targets
project4:
	$(CC) $(CCFLAGS) project4.cpp $(LIBS) -o project4
	./project4

sandbox:
	$(CC) $(CCFLAGS) sandbox.cpp $(LIBS) -o sandbox
	./sandbox
