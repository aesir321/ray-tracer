#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"


using namespace std;

int main()
{
	Vector observer(0, 0, 0, true);
	LightSource pointLightSource(10.0, 10.0, 10.0, true);
	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	Vector spherePos(0, 0, 20, true);
	Sphere sphere(spherePos, 20);
	scene.Populate(sphere);

	Viewport viewport(50, 50, 50);	//Origin is in the middle so magnitude of the x length of the viewport here is 2x2 not 1x1.  
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
