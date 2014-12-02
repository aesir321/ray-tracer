#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"

using namespace std;

int main()
{
	Vector observer(0, 0, 0, true);
	Vector lightSourcePosition(40, 40, 40, true);
	LightSource pointLightSource(lightSourcePosition, 10.0);

	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	Vector spherePos(0, 0, 20, true);
	Sphere *sphere = new Sphere(spherePos, 10);

	scene.Populate(sphere);

	Vector viewportOriginPosition(0, 0, 1, true);
	Viewport viewport(50, 50, 500, 500, viewportOriginPosition);
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
