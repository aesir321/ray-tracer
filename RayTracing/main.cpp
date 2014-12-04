#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"

using namespace std;
/* TODO
	* Overload populate to add all objects.
	* Major cleanup of vector class.
	* Add Plane class.
	* Correctly combine colours
	* Claify why they skew when too close?  Is this correct?
	* Shadows
	*/
int main()
{
	Vector observer(0, 0, 0, true);

	Vector lightSourcePosition(0, 0, 0, true); //y here is inverted: different coord system? right handed?
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white);

	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	Vector spherePos(0, 0, 100, true);
	Sphere *sphere = new Sphere(spherePos, 30);
	RGBColour red(255, 0, 0);
	sphere->SetColour(red);
	scene.Populate(sphere);

	Vector spherePos3(0, 0, 200, true);
	Sphere *sphere3 = new Sphere(spherePos3, 30);
	RGBColour blue(0, 0, 255);
	sphere3->SetColour(blue);
	scene.Populate(sphere3);

	Vector viewportOriginPosition(0, 0, 1, true);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
