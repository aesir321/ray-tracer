CC=g++
CFLAGS=-c -Wall -pedantic
LDFLAGS=
SOURCES=main.cpp Ellipsoid.cpp LightSource.cpp Plane.cpp Ray.cpp RGBColour.cpp Scene.cpp Shape.cpp Sphere.cpp Vector.cpp Viewport.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ray-tracer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@










