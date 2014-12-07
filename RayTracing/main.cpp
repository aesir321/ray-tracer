#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"
#include "Plane.h"

#include <iostream>

using namespace std;
/* TODO
	* Correctly combine colours
	* Shadows
	*/
int main()
{
	Vector observer(0, 0, 0);

	//y here is inverted: different coord system? right handed?
	Vector lightSourcePosition(1000, -1000, 20);
	RGBColour white(1, 1, 1);
	LightSource pointLightSource(lightSourcePosition, white, 0.1);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(observer);

	Vector planeNormal(0, -1, 0);
	RGBColour planeColour(1, 1, 1);
	Plane *plane = new Plane(planeNormal, planeColour, 600);
	scene.Populate(plane);

	Vector spherePos(0, -10, 100);
	Sphere *sphere = new Sphere(spherePos, 50, 0.9, 1);
	RGBColour colour(1, 0, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector viewportOriginPosition(0, 0, 1);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
