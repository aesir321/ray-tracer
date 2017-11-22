CC=g++
CFLAGS=-c -Wall -pedantic -O3
LDFLAGS=
SOURCES=main.cpp Geometry/Ellipsoid.cpp Geometry/LightSource.cpp Geometry/Plane.cpp Geometry/Ray.cpp Rendering/RGBColour.cpp Rendering/Scene.cpp Geometry/Shape.cpp Geometry/Sphere.cpp Geometry/Vector.cpp Rendering/Viewport.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=ray-tracer

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGET) *.o *~










